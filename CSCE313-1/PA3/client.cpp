#include "FIFOreqchannel.h"
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

#include "common.h"

using namespace std;

int main(int argc, char *argv[]){
	int opt;
	int person_num = 1;
	double time = 0.0;
	int ecg_num = 1;
	int req_amt = 0;
	string filename = "";
	// take all the arguments first because some of these may go to the server
	while ((opt = getopt(argc, argv, "p:t:e:f:r:")) != -1) {
		switch(opt) {
			case 'f':
				filename = optarg;
				break;
			case 'p':
				person_num = stoi(optarg);
				break;
			case 't':
				time = stod(optarg);
				break;
			case 'e':
				ecg_num = stoi(optarg);
				break;
			case 'r':
				req_amt = stoi(optarg);
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
	cout << "req_amt:" << req_amt << endl;

	int pid = fork ();
	if (pid < 0){
		EXITONERROR ("Could not create a child process for running the server");
	}
	if (!pid){ // The server runs in the child process
		char* args[] = {"./server", nullptr};
		if (execvp(args[0], args) < 0){
			EXITONERROR ("Could not launch the server");
		}
	}
	FIFORequestChannel chan ("control", FIFORequestChannel::CLIENT_SIDE);

	// ***********   req ONE data point   ***********
	DataRequest d (person_num, time, ecg_num);
	chan.cwrite (&d, sizeof (DataRequest)); // question
	double reply;
	chan.cread (&reply, sizeof(double)); //answer
	if (isValidResponse(&reply)){
		cout << "For person " << person_num <<", at time " << time << ", the value of ecg "<< ecg_num <<" is " << reply << endl;
	}

	// ***********   req 1000 data points and send to x1.csv   ***********
	// keeping track of time
	gettimeofday(&start, NULL);
    // sync the I/O of C and C++.
    ios_base::sync_with_stdio(false);
    //getting the entirety of data points in 1.csv
    ofstream myfile;
    myfile.open("received/x1.csv");
    double i = 0;
  //while ( i < .012){
  cout << "Recieving Data Points..." << endl;
    while ( i < 59.996 ){
      myfile << i << ",";

      datamsg d1 = datamsg(1 , i , 1);
      datamsg d2 = datamsg(1 , i , 2);

      char* buffer1 = new char[sizeof(d1)];
      *(datamsg*)buffer1 = d1;
      chan.cwrite( buffer1, sizeof(datamsg));
      char* ptr1 = chan.cread();
      double data1 = *(double*)ptr1;

      myfile << data1 << ",";

      char* buffer2 = new char[sizeof(d2)];
      *(datamsg*)buffer2 = d2;
      chan.cwrite( buffer2, sizeof(datamsg));
      char* ptr2 = chan.cread();
      double data2 = *(double*)ptr2;

      myfile << data2 << "\n";

      i = i + .004;
    }
    myfile.close();
    cout << "Sucessfully Transferred File Data Points" << endl;


    // stop timer.
    gettimeofday(&end, NULL);
    // Calculating total time taken by the program.
    double time_taken;

    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec -
                              start.tv_usec)) * 1e-6;

    cout << "Time taken to transfer all 1.csv datapoints : " << fixed
         << time_taken << setprecision(6);
    cout << " sec" << endl;




	/* this section shows how to get the length of a file
	you have to obtain the entire file over multiple requests
	(i.e., due to buffer space limitation) and assemble it
	such that it is identical to the original*/
	FileRequest fm (0,0);
	// cout << "filename:" << filename << endl;
	int len = sizeof (FileRequest) + filename.size()+1;
	char buf2 [len];
	memcpy (buf2, &fm, sizeof (FileRequest));
	strcpy (buf2 + sizeof (FileRequest), filename.c_str());
	chan.cwrite (buf2, len);
	int64 filelen;
	chan.cread (&filelen, sizeof(int64));
	if (isValidResponse(&filelen)){
		cout << "File length is: " << filelen << " bytes" << endl;
	}


	// closing the channel
    Request q (QUIT_REQ_TYPE);
    chan.cwrite (&q, sizeof (Request));
	// client waiting for the server process, which is the child, to terminate
	wait(0);
	cout << "Client process exited" << endl;

}
