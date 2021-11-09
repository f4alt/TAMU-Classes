#include "common.h"
#include "FIFOreqchannel.h"
#include "BoundedBuffer.h"
#include "HistogramCollection.h"
#include <sys/wait.h>
#include <thread>
using namespace std;

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

	cout << "recvfname:" << recvfname << endl;

	FileRequest fr (0,0);
	int len = sizeof (FileRequest) + fname.size()+1;
	char buf2 [len];
	memcpy (buf2, &fr, sizeof (FileRequest));
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

	// cout << "FILENAME IN THREAD FUNCT: " << fm->getFileName() << endl;
	while (remlen > 0) {
		fm->length = min(remlen, (__int64_t) mb);
		vector<char> v  = vector<char>((char*)fm, (char*)fm + sizeof(FileRequest));
		request_buffer->push(v);
		// cout << "pushing" << endl;
		fm->offset += fm->length;
		remlen -= fm->length;
	}

	// ----------------------

	// FileRequest fm (0,0);
	// cout << "fname:" << fname << endl;
	// int len = sizeof (FileRequest) + fname.size()+1;
	// char buf2 [len];
	// memcpy (buf2, &fm, sizeof (FileRequest));
	// strcpy (buf2 + sizeof (FileRequest), fname.c_str());
	// chan->cwrite (buf2, len);
	// int64 filelen;
	// chan->cread (&filelen, sizeof(int64));
	// // if (isValidResponse(&filelen)){
	// 	cout << "File length is: " << filelen << " bytes" << endl;
	// // }
	//
  // int num_requests = ceil (double(filelen)/mb);
	//
  // FileRequest* fc = (FileRequest*) buf2;
  // if (num_requests == 1) { // edge case
  //     fc->offset = 0;
  //     fc->length = filelen;
  // } else {
  //     fc->length = mb;
  //     fc->offset = 0;
  // }
  // int64 last_req = filelen - mb* (num_requests-1);
  // chan->cwrite(buf2, len);
	// char response[mb];
  // chan->cread(response,mb);
	//
  // string outputfilepath = string("recv/") + fname;
  // FILE* fp = fopen(outputfilepath.c_str(),"wb");
	// fseek(fp, filelen, SEEK_SET);
	//
	// // send one call incase req only needs one
  // // fwrite(response, 1, fc->length, fp);
	// vector<char> v = vector<char>((char*)&response, (char*)&response + sizeof(FileRequest));
	// request_buffer->push(v);
	//
  // for (int i = 1; i < num_requests; i++) {	// starting from i=1
  //     if (i == num_requests-1) {	// last call
  //         fc->length = last_req;
	// 				char last_res[last_req];
  //         fc->offset += mb;
  //         chan->cwrite(buf2, len);
  //         chan->cread(last_res,mb);
  //         // fwrite(last_res, 1, fc->length, fp);
	// 				FileRequest fr
	// 				vector<char> v = vector<char>((char*)&last_res, (char*)&last_res + sizeof(FileRequest));
	// 				request_buffer->push(v);
	// 				cout << "DONE" << endl;
  //     } else {
  //         fc->offset +=mb;
  //         chan->cwrite(buf2, len);
  //         chan->cread(response,mb);
  //         // fwrite(response, 1, fc->length, fp);
	// 				vector<char> v = vector<char>((char*)&response, (char*)&response + sizeof(FileRequest));
	// 				request_buffer->push(v);
  //     }
  // }
}


// void worker_thread_function(FIFORequestChannel* chan, BoundedBuffer* req_buf, BoundedBuffer* hist_buf, HistogramCollection* hc){
void worker_thread_function(FIFORequestChannel* chan, BoundedBuffer* request_buffer, HistogramCollection* hc, int mb){
	vector<char> msg;
	double resp = 0;

	char recvbuf[mb];
	while(1) {
		msg = request_buffer->pop();
		Request* r = (Request*)msg.data();

		if (r->getType() == DATA_REQ_TYPE) {
			// cout << "data req" << endl;
			chan->cwrite((char*)r, sizeof(DataRequest));
			chan->cread(&resp, sizeof(double));
			hc->update(((DataRequest*)r)->person, resp);
		} else if (r->getType() == FILE_REQ_TYPE) {
			cout << "file type req" << endl;
			FileRequest* fm = (FileRequest*)r;
			// string fname = (char*)(fm + 1);
			// string fname = fm->getFileName();
			string fname = ((FileRequest*)r)->getFileName();
			cout << "filename: " << fname << endl;
			int sz = sizeof(FileRequest) + fname.size() + 1;
			chan->cwrite((char*)r, sz);
			chan->cread(recvbuf, mb);

			string recvfname = "recv/" + fname;
			// string recvfname = "recv/10.csv";
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


void histogram_thread_function () {

}

// static void alarm_handler(int sig, siginfo_t* info, void* ucontext) {
// 	counter_map_t& counters = *(counter_map_t*)info->si_ptr;
// 	system("clear");
//
// 	std::cout << make_histogram_table(counters) << endl;
// }


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
	HistogramCollection hc;

	// create one histogram per patient and add to collection
	for (int i = 0; i < p; i++) {
		Histogram* h = new Histogram(10, -2.0, 2.0);
		hc.add(h);
	}

	// make worker channels
	FIFORequestChannel* wchans[w];
	for (int i = 0; i < w; i++) {
		wchans[i] = create_channel(&chan);
	}

	struct timeval start, end;
    gettimeofday (&start, 0);

    /* Start all threads here */

		// INSTEAD OF PATIENT, WE CALL FILE THREAD - SET THIS WITH FLAG LATER
		thread patient[p];
		if (!file_req_flag) {

			for (int i=0; i < p; i++) {
				patient[i] = thread(patient_thread_function, n, i+1, &request_buffer);
			}
		} else {
			thread filethread (file_thread_function, filename, &request_buffer, &chan, m);
		}

		thread workers[w];
		for (int i = 0; i < w; i++) {
			workers[i] = thread(worker_thread_function, wchans[i], &request_buffer, &hc, m);
		}

		/* Join all threads here */
		// INSTEAD - FIX HERE TOO
		if (!file_req_flag) {
			for (int i = 0; i < p; i++) {
				patient[i].join();
			}
		} else {
			filethread.join();
			cout << "file thread joined" << endl;
		}

		for (int i =0; i<w; i++) {
			Request q (QUIT_REQ_TYPE);
			vector<char> v = vector<char>((char*)&q, (char*)&q + sizeof(Request));
			request_buffer.push(v);
		}
		for (int i=0; i<w; i++) {
			workers[i].join();
		}

    gettimeofday (&end, 0);

    // print the results and time difference
	hc.print ();
    int secs = (end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)/(int) 1e6;
    int usecs = (int)(end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)%((int) 1e6);
    cout << "Took " << secs << " seconds and " << usecs << " micro seconds" << endl;


		// CLEAN UP CHANNELS
		Request q (QUIT_REQ_TYPE);
		for (int i = 0; i < p; i++) {
			wchans[i]->cwrite(&q, sizeof(Request));
		}
    chan.cwrite (&q, sizeof (Request));

	// client waiting for the server process, which is the child, to terminate
	wait(0);
	cout << "Client process exited" << endl;

}
