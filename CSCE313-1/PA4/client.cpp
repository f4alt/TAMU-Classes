#include "common.h"
#include "FIFOreqchannel.h"
#include "BoundedBuffer.h"
#include "HistogramCollection.h"
#include <sys/wait.h>
#include <thread>
using namespace std;


struct hist_upd_args {
	int person;
	double resp;
};

struct hist_coll_access {
	HistogramCollection* hc;
};
hist_coll_access* hc_access;

FIFORequestChannel* create_channel(FIFORequestChannel* chan) {
	Request nc (NEWCHAN_REQ_TYPE);
	chan->cwrite(&nc, sizeof(Request));
	char buf3[1024];
	chan->cread(buf3, sizeof(buf3));
	string new_chan_name = buf3;

	// cout << "new channel created, name: " << new_chan_name << endl;
	FIFORequestChannel* new_chan = new FIFORequestChannel(new_chan_name, FIFORequestChannel::CLIENT_SIDE);

	return new_chan;
}

void patient_thread_function(int n, int pno, BoundedBuffer* request_buffer) {
	DataRequest d(pno, 0.0, 1);
	for (int i =0; i < n; i++) {
		vector<char> v = vector<char>((char*)&d, (char*)&d + sizeof(DataRequest));
		request_buffer->push(v);
		d.seconds += .004;
	}
}

void file_thread_function(string fname, BoundedBuffer* request_buffer, FIFORequestChannel* chan, int mb) {
	string recvfname = "recv/" + fname;

	// cout << "recvfname:" << recvfname << endl;

	FileRequest fr (0,0);
	int len = sizeof (FileRequest) + fname.size()+1;
	char buf2 [len];
	memcpy (&buf2, &fr, sizeof (FileRequest));
	strcpy (buf2 + sizeof (FileRequest), fname.c_str());
	chan->cwrite (buf2, len);
	int64 filelen;
	chan->cread (&filelen, sizeof(int64));

	// create, open and set length of file
	FILE* fp = fopen(recvfname.c_str(), "wb");
	fseek(fp, filelen, SEEK_SET);
	fclose(fp);

	FileRequest* fm = (FileRequest*) buf2;
	__int64_t remlen = filelen;

	while (remlen > 0) {
		fm->length = min(remlen, (__int64_t) mb);
		vector<char> v  = vector<char>((char*)&buf2, (char*)&buf2 + sizeof(FileRequest) + fname.size() + 1);
		request_buffer->push(v);
		fm->offset += fm->length;
		remlen -= fm->length;
	}
}

void worker_thread_function(FIFORequestChannel* chan, BoundedBuffer* request_buffer, BoundedBuffer* response_buffer, int mb){
	vector<char> msg;
	double resp = 0;

	char recvbuf[mb];
	while(1) {
		msg = request_buffer->pop();
		Request* r = (Request*)msg.data();

		if (r->getType() == DATA_REQ_TYPE) {
			chan->cwrite((char*)r, sizeof(DataRequest));
			chan->cread(&resp, sizeof(double));
			hist_upd_args upd_hist = { ((DataRequest*)r)->person, resp };
			vector<char> v = vector<char>((char*)&upd_hist, (char*)&upd_hist + sizeof(hist_upd_args));
			response_buffer->push(v);
		} else if (r->getType() == FILE_REQ_TYPE) {
			// cout << "file type req" << endl;
			FileRequest* fm = (FileRequest*)r;
			string fname = fm->getFileName();
			int sz = sizeof(FileRequest) + fname.size() + 1;
			chan->cwrite((char*)r, sz);
			chan->cread(recvbuf, mb);

			string recvfname = "recv/" + fname;
			FILE* fp = fopen(recvfname.c_str(), "r+");
			fseek(fp, fm->offset, SEEK_SET);
			fwrite(recvbuf, 1, fm->length, fp);
			fclose(fp);
		} else if (r->getType() == QUIT_REQ_TYPE) {
			chan->cwrite(r, sizeof(Request));
			delete chan;
			break;
		}
	}
}


void histogram_thread_function (BoundedBuffer* response_buffer, HistogramCollection* hc) {
	vector<char> msg;

	while(1) {
		msg = response_buffer->pop();
		hist_upd_args* r = (hist_upd_args*)msg.data();

		if (r->person > 0) {
			hc->update(r->person, r->resp);
		} else if (r->person == -1) {		// sending person = -1 == quit message
			break;
		}
	}

}

static void alarm_handler(int signum) {
	// clear screen and move cursor to top
	std::cout << "\033[2J\033[H" << std::flush;

  // print the histogram
  hc_access->hc->print();

  // set alarm again
  alarm(2);
}


int main(int argc, char *argv[]){

	int opt;
	double t = 0.0;
	int file_req_flag = 0;
	/* we need
	n: number of data points
	p: number of patients (starting from 1)
	w: number of worker threads
	b: request buffer size
	m: buffer capacity
	f: file name
	h: number of histogram threads
	*/
	int n = 1000;
	int p = 1;
	int w = 10;
	int b = 20; // size of bounded buffer, note: this is different from another variable buffercapacity/m
	int m = 256;
	string filename = "";
	int h = 1;

	// take all the arguments first because some of these may go to the server
	while ((opt = getopt(argc, argv, "n:p:w:b:m:f:h:")) != -1) {
		switch(opt) {
			case 'n':
				n = stoi(optarg);
				break;
			case 'p':
				p = stoi(optarg);
				break;
			case 'w':
				w = stoi(optarg);
				break;
			case 'b':
				b = stoi(optarg);
				break;
			case 'm':
				m = stoi(optarg);
				break;
			case 'f':
				filename = optarg;
				file_req_flag = 1;
				break;
			case 'h':
				h = stoi(optarg);
				break;
			case '?':
        if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
		}
	}

	// verify user inputs
	cout << " -- verify user inputs -- " << endl;
	cout << "n:" << n << endl;
	cout << "p:" << p << endl;
	cout << "w:" << w << endl;
	cout << "b:" << b << endl;
	cout << "m:" << m << endl;
	cout << "f:" << filename << endl;
	cout << "h:" << h << endl;
	cout << "-------" << endl;


	int pid = fork ();
	if (pid < 0){
		EXITONERROR ("Could not create a child process for running the server");
	}
	if (!pid){ // The server runs in the child process
		char buffer_size_string[7 + sizeof(char)];
		sprintf(buffer_size_string, "%d", m);
		char* args[] = {"./server", "-m", buffer_size_string, nullptr};
		if (execvp(args[0], args) < 0){
			EXITONERROR ("Could not launch the server");
		}
	}
	FIFORequestChannel chan ("control", FIFORequestChannel::CLIENT_SIDE);
	BoundedBuffer request_buffer(b);
	BoundedBuffer response_buffer(b);
	HistogramCollection hc;

	hc_access = static_cast<hist_coll_access *>(malloc(sizeof(hist_coll_access)));
    memset(hc_access, 0, sizeof(hist_coll_access));

    hc_access->hc = &hc;

    signal(SIGALRM, AlarmHandler);
    alarm(2);

	// create one histogram per patient and add to collection
	for (int i = 0; i < p; i++) {
		Histogram* h = new Histogram(10, -2.0, 2.0);
		hc.add(h);
	}
	cout << "created " << p << " histogram(s)" << endl;

	// make worker channels
	FIFORequestChannel* wchans[w];
	for (int i = 0; i < w; i++) {
		wchans[i] = create_channel(&chan);
	}
	cout << "created " << w << " worker channel(s)" << endl;

	struct timeval start, end;
    gettimeofday (&start, 0);

    /* Start all threads here */

		// INSTEAD OF PATIENT THREADS, WE CREATE FILE THREAD
		thread patient[p];
		thread histograms[h];
		thread filethread;
		if (!file_req_flag) {
			// create p patient threads
			for (int i=0; i < p; i++) {
				patient[i] = thread(patient_thread_function, n, i+1, &request_buffer);
			}
			cout << "created " << p << " patient thread(s)" << endl;

			// create h histogram threads
			for (int i=0; i < h; i++) {
				histograms[i] = thread(histogram_thread_function, &response_buffer, &hc);
			}
			cout << "created " << h << " histogram thread(s)" << endl;
		} else {
			// create file thread
			filethread = thread(file_thread_function, filename, &request_buffer, &chan, m);
			cout << "created 1 file thread" << endl;
		}

		// create w worker threads
		thread workers[w];
		for (int i = 0; i < w; i++) {
			workers[i] = thread(worker_thread_function, wchans[i], &request_buffer, &response_buffer, m);
		}
		cout << "created " << w << " worker threads(s)" << endl;

		/* Join all threads here */
		if (!file_req_flag) {
			// join patientes
			for (int i = 0; i < p; i++) {
				patient[i].join();
			}
			cout << "patients joined" << endl;
		} else {
			// join filethread
			filethread.join();
			cout << "file thread joined" << endl;
		}

		for (int i =0; i<w; i++) {
			// set quit messages to worker channels
			Request q (QUIT_REQ_TYPE);
			vector<char> v = vector<char>((char*)&q, (char*)&q + sizeof(Request));
			request_buffer.push(v);
		}
		for (int i=0; i<w; i++) {
			// join worker threads
			workers[i].join();
		}
		cout << "workers joined" << endl;

		if (!file_req_flag) {
			// send quit message to histogram threads
			hist_upd_args q = { -1, -1 };
			for (int i=0; i < h; i++) {
				vector<char> v = vector<char>((char*)&q, (char*)&q + sizeof(hist_upd_args));
				response_buffer.push(v);
			}

			// join histogram threads
			for (int i = 0; i < h; i++) {
				histograms[i].join();
			}
			cout << "histograms joined" << endl;
		}

    gettimeofday (&end, 0);

    // print the results and time difference
		if (!file_req_flag) {
			// hc.print ();
		}
    int secs = (end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)/(int) 1e6;
    int usecs = (int)(end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)%((int) 1e6);
    cout << "Took " << secs << " seconds and " << usecs << " micro seconds" << endl;


		// quit main channel
		Request q (QUIT_REQ_TYPE);
    chan.cwrite (&q, sizeof (Request));
		cout << "all channels cleaned up" << endl;

	// client waiting for the server process, which is the child, to terminate
	wait(0);
	cout << "Client process exited" << endl;

}
