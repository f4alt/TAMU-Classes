#include "common.h"
#include "BoundedBuffer.h"
#include "Histogram.h"
#include "common.h"
#include "HistogramCollection.h"
#include "FIFOreqchannel.h"
using namespace std;


class patient_thread_args{
public:
   /*put all the arguments for the patient threads */
   pthread_t thread;
   //added
   //how many reuests to make
   int requestCount;
   //person for whom to get info
   int patientNumber;
   //buffer to put requests into
   BoundedBuffer * requestBuffer;

   patient_thread_args(int RequestCount, int PatientNumber, BoundedBuffer* RequestBuffer){
     requestCount = RequestCount;
     patientNumber = PatientNumber;
     requestBuffer = RequestBuffer;
   }
   patient_thread_args(){

   }

};

class worker_thread_args{
public:
   /*put all the arguments for the worker threads */
   //added
   pthread_t thread;
   //request channel to server
   FIFORequestChannel *workerChannel;
   //buffer from which to get requests
   BoundedBuffer * requestBuffer;
   //histogram that is updated by data processes
   BoundedBuffer **statBuffer;

   worker_thread_args(FIFORequestChannel* Channel, BoundedBuffer* Buffer, BoundedBuffer** StatBuffer){
      workerChannel = Channel;
      requestBuffer = Buffer;
      //hist = Hist;
      statBuffer = StatBuffer;

   }
   worker_thread_args(){

   }

};

void *patient_thread_function(void *arg)
{
    /* What will the patient threads do? */

    //added
    patient_thread_args *args = (patient_thread_args *)arg;

    double seconds = 0.000;
    double stepSize = 0.004;

		// OLD
    // datamsg dm(args->patientNumber, seconds, 1);
		DataRequest dm(args->patientNumber, seconds, 1);

    for (int i = 0 ; i < args->requestCount; i ++){
      //arg->requestBuffer->push(args->name);
			// OLD
      // args->requestBuffer->push((char*) &dm, sizeof(datamsg));
			vector<char> v = vector<char>((char*)&dm, (char*)&dm + sizeof(DataRequest));
			args->requestBuffer->push(v);
      dm.seconds += stepSize;
    }

}

void *worker_thread_function(void *arg)
{
    /*
		Functionality of the worker threads
    */

    //added
    worker_thread_args *args = (worker_thread_args *)arg;
		char* resp;
    //FIFORequestChannel *workerChannel = args->channel;
    while(true){
        vector<char> request = args->requestBuffer->pop();
        char* command = (char *) request.data();
      //  workerChannel->cwrite(command, sizeof(MESSAGE_TYPE) );
        if(*(REQUEST_TYPE_PREFIX *)command == QUIT_REQ_TYPE){
          args->workerChannel->cwrite(command, sizeof(REQUEST_TYPE_PREFIX));
          break;
        }
        else if(*(REQUEST_TYPE_PREFIX *)command == DATA_REQ_TYPE){
          DataRequest * dm = (DataRequest *) command;
          args->workerChannel->cwrite(command, sizeof(DataRequest));
					args->workerChannel->cread(&resp, sizeof(char*));
          // char* response = args->workerChannel->cread();

          delete resp;
        }
        else if (*(REQUEST_TYPE_PREFIX *)command == FILE_REQ_TYPE){
          //nothing
        }
        //Datamsg* data = (datamsg*) command;
        // MESSAGE_TYPE m = *(MESSAGE_TYPE *) command;
        // if(m == QUIT_MSG ){
        //   delete args->channel;
        //   break;
        // }
        // else{
        //   char* response = workerChannel->cread();
        //   args->hist->(request, response);
        // }
        //if(data.)
        // vector <char> request = buffer->pop()
        // Char* pointer = request.data()
        // Datamsg* data = (datamsg*) pointer
        //args->channel->cwrite(request );
        //args->channel->cwrite( command, sizeof(command) );
        //delete worker channel if request is quit
        // if (request == "quit"){
        //   delete args->channel;
        //   break;
        // }
        // else{
        // }
    }
}




/* Main Function */

int main(int argc, char *argv[])
{
    int n = 100;    //default number of requests per "patient"
    int w = 10;    //default number of worker threads
    int b = 20; 	// default capacity of the request buffer, you should change this default

    int p = 1;     // number of patients [1,15]
    int m = MAX_MESSAGE; 	// default capacity of the file buffer
    srand(time_t(NULL));

    //file name
    //if f isn't null, switch modes
    string f = "";

    //added
    //accept input arguments
    int opt = 0;
    while ((opt = getopt(argc, argv, "n:p:w:b:m:")) != -1) {
        switch (opt) {
          //number of requests per patient
            case 'n':
                n = atoi(optarg);
                break;
          //number of patients
            case 'p' :
                p = atoi(optarg);
                break;
          //capacity of the request buffer
            case 'b':
                b = atoi(optarg);
                //This won't do a whole lot until you fill in the worker thread function
                break;
          //number of worker threads
            case 'w':
                w = atoi(optarg);
                //This won't do a whole lot until you fill in the worker thread function
                break;
          //name of the file to be retrieved
            case 'f':
                f = optarg;
          //capacity of the file buffer
            case 'm':
                m = atoi(optarg);
                break;
			}
    }


    int pid = fork();
    //dataserver side
    if (pid == 0){
		// modify this to pass along m
        execl ("dataserver", "dataserver", (char *)NULL);

    }
    //added
    //client side


      if(f == ""){
        cout << "n ==" << n << endl;
        cout << "w ==" << w << endl;
        cout << "p ==" << p << endl;
        cout << "b ==" << b << endl;

        cout << "Client Started" << endl;
        cout << "File Request" << endl;
      }
      else if(f != ""){
        cout << "File Name: " << f << endl;
        cout << "Client Started" << endl;
        cout << "Data Request" << endl;
      }


    cout << "Initializing Control Channel..." << endl;
	  FIFORequestChannel* chan = new FIFORequestChannel("control", FIFORequestChannel::CLIENT_SIDE);
    cout << "Finished Initializing Control Channel." << endl;
    BoundedBuffer request_buffer(b);
	  HistogramCollection hc;


    string patientsList [] = {"Patient 1", "Patient 2", "Patient 3, Patient 4",
                          "Patient 5", "Patient 6", "Patient 7", "Patient 8",
                            "Patient 9", "Patient 10", "Patient 11", "Patient 12",
                            "Patient 13", "Patient 14", "Patient 15"};

    //establish patient_thread_args
    BoundedBuffer **statBuffer = new BoundedBuffer *[p];
    for (int i = 0; i < p; i++){
      statBuffer[i] = new BoundedBuffer(ceil(b/1.0/p));
    }
    //
    //
    // vector<patient_thread_args *> patients;
    // vector<worker_thread_args *> workers;
    //
    // //for files
    // // vector<patients_thread_for_file *> patientsf;
    // // vector<worker_thread_for_file *> workersf;
    //
    // for(int i = 0; i < p ; i++){
    //   patient_thread_args *ptemp = new patient_thread_args(n, i+1, &request_buffer);
    //   patients.push_back(ptemp);
    // }
    //
    // for(int i = 0; i < w; i++){
    //   MESSAGE_TYPE m = NEWCHANNEL_MSG;
    //   chan->cwrite ((char *) &m, sizeof (MESSAGE_TYPE));
    //   string chan_name = chan->cread();
    //   FIFORequestChannel* wchan = new FIFORequestChannel (chan_name, FIFORequestChannel::CLIENT_SIDE);
    //   worker_thread_args* temp = new worker_thread_args (wchan, &request_buffer, statBuffer);
    //   workers.push_back (temp);
    // }
    //

    //code for file
    struct timeval start, end;
    gettimeofday (&start, 0);



    //
    // for(int i = 0; i < p; i++){
    //   pthread_create(&patients[i]->thread, NULL, patient_thread_function, patients[i]);
    // }
    // for(int i = 0; i < w; ++i){
    //   pthread_create(&workers[i]->thread, NULL, worker_thread_function, workers[i]);
    // }
    //
    // for(int i = 0; i < p ; i++){
    //   pthread_join(patients[i]->thread, 0);
    // }
    // cout << "Sending Requests... " << endl;
    // for (int i = 0 ; i < w ; ++i){
    //     MESSAGE_TYPE m = QUIT_MSG;
    //     request_buffer.push((char*)&m, sizeof(MESSAGE_TYPE));
    // }
    //
    // cout << "Finished Requests. " << endl;
    // for (int i = 0; i < w ; i++){
    //   pthread_join(workers[i]->thread, 0);
    // }
    //
    // cout << "Does it get this far?" << endl;

    // for(int i = 0 ; i < p ; i++){
    //   pthread_join (stats[i]->thread, 0);
    // }

    //more file code



    //array of patients channels equal in size to p input

    patient_thread_args* ptas [p];
    for (int i = 0 ; i < p ; i++){
      ptas[i]->patientNumber = i;
      ptas[i]->requestCount = n;
      ptas[i]->requestBuffer = & request_buffer;
    }

    //establish worker_thread_args


    //array of worker thread chanels equal to input
    worker_thread_args* wtas [w];
    for (int i = 0 ; i < w ; i++){
      wtas[i]->requestBuffer = & request_buffer;
      for(int j = 0 ; j < w ; j++){
        wtas[i]->statBuffer[j] = statBuffer[j];
      }
      REQUEST_TYPE_PREFIX q = NEWCHAN_REQ_TYPE;
      chan->cwrite ((char *) &q, sizeof (REQUEST_TYPE_PREFIX));

			string s;
			chan->cread(&s, sizeof(string));
      // string s = chan->cread();
      FIFORequestChannel *workerChannel = new FIFORequestChannel(s, FIFORequestChannel::CLIENT_SIDE);
      wtas[i]->workerChannel = new FIFORequestChannel(s, FIFORequestChannel::CLIENT_SIDE);;

      pthread_t worker;
      //worker_thread_args *args = new worker_thread_args(workerChannel, &request_buffer, &hc);
      worker_thread_args* args = new worker_thread_args (workerChannel, &request_buffer, statBuffer);
      pthread_create(&worker, NULL, worker_thread_function, args);

      //workers.push_back(worker);
      //wtas[i] = args;
    }




    /* Start all threads here */


    pthread_t pts [p];
    for (int i = 0 ; i < p; i++){
      pthread_create (&pts [i], 0, patient_thread_function, &ptas [i]);
    }

    cout << "Running Worker Threads..." << endl;
    pthread_t wts [w];
    for (int i = 0; i < w ; i++){
      pthread_create (&wts[i], 0, worker_thread_function, &wtas [i]);
    }

    for(int i = 3; i < p; i++){
      pthread_join(pts [i], 0);
    }
    cout << "Patient Request Threads Completed" << endl;

    //quit all the worker Channels
    for(int i = 0 ; i < w ; i++){
      REQUEST_TYPE_PREFIX q = QUIT_REQ_TYPE;
      //chan->cwrite ((char *) &q, sizeof (MESSAGE_TYPE));
      // request_buffer.push((char *) &q, sizeof (REQUEST_TYPE_PREFIX));
			vector<char> v = vector<char>((char*)&q, (char*)&q + sizeof(REQUEST_TYPE_PREFIX));
			request_buffer.push(v);
    }
    for(int i = 0 ; i < w ; i++){
      pthread_join (wts[i], 0);
    }
    cout << "Worker Threads Finished" << endl;


	  /* Join all threads here */
    gettimeofday (&end, 0);
	  hc.print ();
    int secs = (end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)/(int) 1e6;
    int usecs = (int)(end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)%((int) 1e6);
    cout << "Took " << secs << " seconds and " << usecs << " micor seconds" << endl;


    //quits the server and then deletes the channel
    REQUEST_TYPE_PREFIX q = QUIT_REQ_TYPE;
    chan->cwrite ((char *) &q, sizeof (REQUEST_TYPE_PREFIX));
    cout << "All Done!!!" << endl;


    //deletes worker and patient Threads
    for (int i = 0 ; i < p ; i++){
      delete ptas[i];
    }
    for(int i = 0 ; i < w; i++){
      delete wtas[i]->workerChannel;
      delete wtas[i];
    }

    delete chan;


}




// #include "common.h"
// #include "FIFOreqchannel.h"
// #include "BoundedBuffer.h"
// #include "HistogramCollection.h"
// #include <sys/wait.h>
// #include <thread>
// using namespace std;
//
// FIFORequestChannel* create_channel(FIFORequestChannel* chan, int buffer_size) {
// 	Request nc (NEWCHAN_REQ_TYPE);
// 	chan->cwrite(&nc, sizeof(Request));
// 	char buf3[buffer_size];
// 	chan->cread(buf3, sizeof(buf3));
// 	string new_chan_name = buf3;
//
// 	// cout << "new channel created, name: " << new_chan_name << endl;
// 	FIFORequestChannel* new_chan = new FIFORequestChannel(new_chan_name, FIFORequestChannel::CLIENT_SIDE);
//
// 	return new_chan;
//
// 	// return FIFORequestChannel(new_chan_name, FIFORequestChannel::CLIENT_SIDE);
// }
//
// void patient_thread_function(int n, int pat_num, BoundedBuffer* req_buf) {
// 	DataRequest d(pat_num, 0.0, 1);
// 	// double resp = 0;
//
// 	for (int i=0; i < n; i++) {
// 		// chan->cwrite(&d, sizeof(DataRequest));
// 		// chan->cread(&resp, sizeof(double));
// 		// hc->update(pat_num, resp);
//
//
// 		vector<char> v = vector<char>((char*)&d, (char*)&d + sizeof(DataRequest));
// 		req_buf->push(v);
//
// 		// req_buf->push((char*)&d, sizeof(DataRequest));
// 		d.seconds += 0.004;
// 	}
// }
//
//
// // void worker_thread_function(FIFORequestChannel* chan, BoundedBuffer* req_buf, BoundedBuffer* hist_buf, HistogramCollection* hc){
// void worker_thread_function(FIFORequestChannel* chan, BoundedBuffer* req_buf, HistogramCollection* hc){
// 	double resp = 0;
// 	while (1) {
// 		vector<char> req = req_buf->pop();
// 		// char* data = req.data();
// 		// Request* r = (Request*)data;
// 		Request* r = (Request*)req.data();
//
// 		if (r->getType() == DATA_REQ_TYPE) {
// 			// cout << "data req" << endl;
// 			// DataRequest* dm = (DataRequest*)r;
// 			chan->cwrite(&r, sizeof(DataRequest));
// 			// cout << "why are we reading here" << endl;
// 			chan->cread(&resp, sizeof(double));
// 			cout << "updating person:" << ((DataRequest*)r)->person << endl;
// 			hc->update(((DataRequest*)r)->person, resp);
//
// 			// hist_buf->push((char*)&dm, sizeof(DataRequest));
// 		}  if (r->getType() == FILE_REQ_TYPE) {
// 			cout << "file req" << endl;
// 			// int flen = sizeof(FileRequest) + sizeof(filename) + 1;
// 			// char buf[flen];
// 			// vector<char> v = vector<char>((char*)&buf, (char*)&buf + flen);
// 			// req_buf->push(v);
// 		}  if (r->getType() == QUIT_REQ_TYPE) {
// 			cout << "quit req" << endl;
// 			chan->cwrite(&r, sizeof(Request));
// 			delete chan;
// 			break;
// 		}
// 	}
// }
//
//
// void histogram_thread_function (FIFORequestChannel* chan, BoundedBuffer* hist_buf, HistogramCollection* hc){
// 	double resp = 0;
// 	// while (1) {
// 	// 	vector<char> req = hist_buf->pop();
// 	// 	char* m = (char*)req.data();
// 	//
// 	// 	if (*(REQUEST_TYPE_PREFIX*)m == DATA_REQ_TYPE) {
// 	// 		DataRequest* dm = (DataRequest*)m;
// 	// 		// hist_buf->push((char*)&dm, sizeof(DataRequest));
// 	// 		chan->cwrite(&dm, sizeof(DataRequest));
// 	// 		chan->cread(&resp, sizeof(double));
// 	// 		hc->update(((DataRequest*)dm)->person, resp);
// 	// 	}
// 	// }
// }
//
//
// int main(int argc, char *argv[]){
//
// 	int opt;
// 	double t = 0.0;
// 	int file_req_flag = 0;
// 	/* we need
// 	n: number of data points
// 	p: number of patients (starting from 1)
// 	w: number of worker threads
// 	b: request buffer size
// 	m: buffer capacity
// 	f: file name
// 	h: number of histogram threads
// 	*/
// 	int n = 1000;
// 	int p = 1;
// 	int w = 10;
// 	int b = 20; // size of bounded buffer, note: this is different from another variable buffercapacity/m
// 	int m = 256;
// 	string filename = "";
// 	int h = 1;
//
// 	// take all the arguments first because some of these may go to the server
// 	while ((opt = getopt(argc, argv, "n:p:w:b:m:f:h:")) != -1) {
// 		switch(opt) {
// 			case 'n':
// 				n = stoi(optarg);
// 				break;
// 			case 'p':
// 				p = stoi(optarg);
// 				break;
// 			case 'w':
// 				w = stoi(optarg);
// 				break;
// 			case 'b':
// 				b = stoi(optarg);
// 				break;
// 			case 'm':
// 				m = stoi(optarg);
// 				break;
// 			case 'f':
// 				filename = optarg;
// 				file_req_flag = 1;
// 				break;
// 			case 'h':
// 				h = stoi(optarg);
// 				break;
// 			case '?':
//         if (isprint (optopt))
//           fprintf (stderr, "Unknown option `-%c'.\n", optopt);
//         else
//           fprintf (stderr,
//                    "Unknown option character `\\x%x'.\n",
//                    optopt);
//         return 1;
//       default:
//         abort ();
// 		}
// 	}
//
//
// 	int pid = fork ();
// 	if (pid < 0){
// 		EXITONERROR ("Could not create a child process for running the server");
// 	}
// 	if (!pid){ // The server runs in the child process
// 		char buffer_size_string[7 + sizeof(char)];
// 		sprintf(buffer_size_string, "%d", m);
// 		char* args[] = {"./server", "-m", buffer_size_string, nullptr};
// 		if (execvp(args[0], args) < 0){
// 			EXITONERROR ("Could not launch the server");
// 		}
// 	}
// 	FIFORequestChannel chan ("control", FIFORequestChannel::CLIENT_SIDE);
// 	BoundedBuffer request_buffer(b);
// 	BoundedBuffer histogram_buffer(b);
// 	HistogramCollection hc;
//
// 	// make p histograms and add to collection - ie 1 per person
// 	for (int i =0; i < p; i++) {
// 		Histogram* h = new Histogram(10, -2.0, 2.0);
// 		hc.add(h);
// 	}
//
// 	// create w worker channels
// 	FIFORequestChannel* wchans[p];
// 	for (int i =0; i < w; i++) {
// 		wchans[i] = create_channel(&chan, m);
//
// 		// Request nc (NEWCHAN_REQ_TYPE);
// 		// chan.cwrite(&nc, sizeof(Request));
// 		// char buf3[m];
// 		// chan.cread(buf3, sizeof(buf3));
// 		// string new_chan_name = buf3;
// 		//
// 		// // cout << "new channel created, name: " << new_chan_name << endl;
// 		// wchans[i] = new FIFORequestChannel(new_chan_name, FIFORequestChannel::CLIENT_SIDE);
// 	}
// 	cout << "created " << w << " worker channels" << endl;
//
//
//
//
// 	struct timeval start, end;
//     gettimeofday (&start, 0);
//
//     /* Start all threads here */
//
// 		// start p patient threads
// 		thread patient[p];
// 		for (int i =0; i < p; i++) {
// 			patient[i] = thread(patient_thread_function, n, i+1, &request_buffer);
// 		}
// 		cout << "started " << p << " patient thread(s)" << endl;
//
// 		thread workers[w];
// 		for (int i = 0; i < w; i++) {
// 			// workers[i] = thread(worker_thread_function, wchans[i], &request_buffer, &histogram_buffer, &hc);
// 				workers[i] = thread(worker_thread_function, wchans[i], &request_buffer, &hc);
// 		}
// 		cout << "started " << w << " worker thread(s)" << endl;
//
// 		thread hists[h];
// 		for (int i =0; i < h; i++) {
// 			// hists[i] = thread(histogram_thread_function, &chan, &histogram_buffer, &hc);
// 		}
// 		cout << "started " << h << " hists thread(s)" << endl;
//
//
// 		/* Join all threads here */
// 		for (int i =0; i < p; i++) {
// 			patient[i].join();
// 		}
// 		cout << "patients joined" << endl;
// 		Request q (QUIT_REQ_TYPE);
// 		for (int i = 0; i < w; i++) {
//
// 			vector<char> v = vector<char>((char*)&q, (char*)&q + sizeof(Request));
// 			request_buffer.push(v);
//
// 			// request_buffer.push((char*)&q, sizeof(Request));
// 		}
// 		for (int i =0; i < w; i++) {
// 			workers[i].join();
// 		}
// 		cout << "workers joined" << endl;
// 		for(int i=0; i < h; i++) {
// 			hists[i].join();
// 		}
// 		cout << "hists joined" << endl;
//     gettimeofday (&end, 0);
//
//     // print the results and time difference
// 	hc.print ();
//     int secs = (end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)/(int) 1e6;
//     int usecs = (int)(end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)%((int) 1e6);
//     cout << "Took " << secs << " seconds and " << usecs << " micro seconds" << endl;
//
//
// 		// CLEAN UP ALL CHANNELS
//     // Request q (QUIT_REQ_TYPE);
// 		// clean up worker channels
// 		// for (int i =0; i < p; i++) {
// 		// 	wchans[i]->cwrite(&q, sizeof(Request));
// 		// 	delete wchans[i];
// 		// }
// 		// clean up control
//     chan.cwrite (&q, sizeof (Request));
//
// 	// client waiting for the server process, which is the child, to terminate
// 	wait(0);
// 	cout << "Client process exited" << endl;
//
// }
