#include "common.h"
#include "FIFOreqchannel.h"
#include "BoundedBuffer.h"
#include "HistogramCollection.h"
#include <sys/wait.h>
#include <thread>
using namespace std;

FIFORequestChannel* create_channel(FIFORequestChannel* chan, int buffer_size) {
	Request nc (NEWCHAN_REQ_TYPE);
	chan->cwrite(&nc, sizeof(Request));
	char buf3[buffer_size];
	chan->cread(buf3, sizeof(buf3));
	string new_chan_name = buf3;

	// cout << "new channel created, name: " << new_chan_name << endl;
	FIFORequestChannel* new_chan = new FIFORequestChannel(new_chan_name, FIFORequestChannel::CLIENT_SIDE);

	return new_chan;
}

void patient_thread_function(int n, int pat_num, BoundedBuffer* req_buf) {
	DataRequest d(pat_num, 0.0, 1);
	// double resp = 0;

	for (int i=0; i < n; i++) {
		// chan->cwrite(&d, sizeof(DataRequest));
		// chan->cread(&resp, sizeof(double));
		// hc->update(pat_num, resp);
		vector<char> v = vector<char>((char*)&r, (char*)&r + sizeof(DataRequest));
		req_buf->push(v);
		d.seconds += 0.004;
	}
}


void worker_thread_function(FIFORequestChannel* chan, BoundedBuffer* req_buf, BoundedBuffer* hist_buf, HistogramCollection* hc){
	double resp = 0;
	while (1) {
		vector<char> req = req_buf->pop();
		char* m = req.data();
		Request* r = (Request*)data;

		if (r->getType() == DATA_REQ_TYPE) {
			DataRequest* dm = (DataRequest*)m;
			chan->cwrite(&dm, sizeof(DataRequest));
			chan->cread(&resp, sizeof(double));
			// hist_buf->push((char*)&dm, sizeof(DataRequest));
			hc->update(((DataRequest*)dm)->person, resp);
		} else if (r->getType() == == FILE_REQ_TYPE) {

		} else if (r->getType() == == QUIT_REQ_TYPE) {
			chan->cwrite(&r, sizeof(Request));
			delete chan;
			break;
		}
	}
}


void histogram_thread_function (FIFORequestChannel* chan, BoundedBuffer* hist_buf, HistogramCollection* hc){
	double resp = 0;
	while (1) {
		vector<char> req = hist_buf->pop();
		char* m = (char*)req.data();

		if (*(REQUEST_TYPE_PREFIX*)m == DATA_REQ_TYPE) {
			DataRequest* dm = (DataRequest*)m;
			// hist_buf->push((char*)&dm, sizeof(DataRequest));
			chan->cwrite(&dm, sizeof(DataRequest));
			chan->cread(&resp, sizeof(double));
			hc->update(((DataRequest*)dm)->person, resp);
		}
	}
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
	int p = 10;
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
	BoundedBuffer histogram_buffer(b);
	HistogramCollection hc;

	// make p histograms and add to collection - ie 1 per person
	for (int i =0; i < p; i++) {
		Histogram* h = new Histogram(10, -2.0, 2.0);
		hc.add(h);
	}

	// create w worker channels
	FIFORequestChannel* wchans[p];
	for (int i =0; i < w; i++) {
		wchans[i] = create_channel(&chan, m);
	}
	cout << "created " << w << " worker channels" << endl;




	struct timeval start, end;
    gettimeofday (&start, 0);

    /* Start all threads here */

		// start p patient threads
		thread patient[p];
		for (int i =0; i < p; i++) {
			patient[i] = thread(patient_thread_function, n, i+1, &request_buffer);
		}
		cout << "started " << p << " patient threads" << endl;

		thread workers[w];
		for (int i = 0; i < w; i++) {
			workers[i] = thread(worker_thread_function, wchans[i], &request_buffer, &histogram_buffer, &hc);
		}
		cout << "started " << w << " worker threads" << endl;

		thread hists[h];
		for (int i =0; i < h; i++) {
			hists[i] = thread(histogram_thread_function, &chan, &histogram_buffer, &hc);
		}
		cout << "started " << h << " hists threads" << endl;


		/* Join all threads here */
		for (int i =0; i < p; i++) {
			patient[i].join();
		}
		cout << "patients joined" << endl;
		for (int i = 0; i < w; i++) {
			Request q (QUIT_REQ_TYPE);
			request_buffer.push((char*) &q, sizeof(q));
		}
		for (int i =0; i < w; i++) {
			workers[i].join();
		}
		cout << "workers joined" << endl;
    gettimeofday (&end, 0);

    // print the results and time difference
	hc.print ();
    int secs = (end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)/(int) 1e6;
    int usecs = (int)(end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)%((int) 1e6);
    cout << "Took " << secs << " seconds and " << usecs << " micro seconds" << endl;


		// CLEAN UP ALL CHANNELS
    Request q (QUIT_REQ_TYPE);
		// clean up worker channels
		// for (int i =0; i < p; i++) {
		// 	wchans[i]->cwrite(&q, sizeof(Request));
		// 	delete wchans[i];
		// }
		// clean up control
    chan.cwrite (&q, sizeof (Request));
	// client waiting for the server process, which is the child, to terminate
	wait(0);
	cout << "Client process exited" << endl;

}
