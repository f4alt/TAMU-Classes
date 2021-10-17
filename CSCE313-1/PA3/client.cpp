#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>

#include "common.h"
#include "FIFOreqchannel.h"

using namespace std;

int main(int argc, char *argv[]){
	int opt;
	int person_num = 1;
	double time = 0.0;
	int ecg_num = 1;
	int req_amt = 0;
	int buffer_size = 256;
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

	// ***********   req_amt data points and send to x1.csv   ***********
	if (req_amt > 0) {
		// keeping track of time
		struct timeval start, end;
		gettimeofday(&start, NULL);

		// create / open output file "x1.csv"
	  ofstream outfile;
	  outfile.open("received/x1.csv");

	  double i = 0;
	  cout << "*Starting*\nRequesting " << req_amt << " data points from person " << person_num << " starting at 0 sec" << endl;
		for (int a = 0; a < req_amt; a++) {
	    outfile << i << ",";

			DataRequest ecg1 = DataRequest(person_num, i, 1);
			DataRequest ecg2 = DataRequest(person_num, i, 2);

			// get reply 1 for ecg1
			chan.cwrite (&ecg1, sizeof (DataRequest));
			double reply1;
			chan.cread (&reply1, sizeof(double));

			// write
			outfile << reply1 << ",";

			// get reply 2 for ecg2
			chan.cwrite (&ecg2, sizeof (DataRequest));
			double reply2;
			chan.cread (&reply2, sizeof(double));

			// write to file
			outfile << reply2 << "\n";

			// inc by .004 as this is how csv are incremented
	    i = i + .004;
	  }
		// gracefully close file
	  outfile.close();
	  cout << "*Done Requesting*" << endl;

	  // stop timer.
	  gettimeofday(&end, NULL);
	  // Calculating total time
	  double time_taken;

	  time_taken = (end.tv_sec - start.tv_sec) * 1e6;
	  time_taken = (time_taken + (end.tv_usec -
	                            start.tv_usec)) * 1e-6;

	  cout << "Time taken for " << req_amt << " data points:" << fixed << time_taken << setprecision(6) << " sec" << endl;
	}

	// *********** Requesting files ***********

	/* this section shows how to get the length of a file
	you have to obtain the entire file over multiple requests
	(i.e., due to buffer space limitation) and assemble it
	such that it is identical to the original*/
	// FileRequest fm (0,0);
	// // cout << "filename:" << filename << endl;
	// int len = sizeof (FileRequest) + filename.size()+1;
	// char buf2 [len];
	// memcpy (buf2, &fm, sizeof (FileRequest));
	// strcpy (buf2 + sizeof (FileRequest), filename.c_str());
	// chan.cwrite (buf2, len);
	// int64 filelen;
	// chan.cread (&filelen, sizeof(int64));
	// if (isValidResponse(&filelen)){
	// 	cout << "File length is: " << filelen << " bytes" << endl;
	// }

	// open output file
	//cout << "We have a file" <<endl;
            FileRequest f(0, 0);
            int size_total = sizeof(FileRequest) + filename.size() + 1;// we cant append the filemesage with the filename,
            //so we need to create a buffer to hold both of those variables. In reality we need to send 1 more byte and that is the
            //null byte
            //need to create pointer to buffer of the size of everything together
            //cout << "size total" <<size_total <<endl;
            char *buf = new char[size_total];
            memcpy(buf, &f, sizeof(FileRequest));
            //buffer has the file message, but we need to append the filename as well
            strcpy(buf + sizeof(FileRequest), filename.c_str());

            chan.cwrite(buf, size_total);
            __int64_t fs;
            chan.cread(&fs,sizeof(__int64_t));
            //cout << "total file size: " << fs << endl;
            int num_messages = ceil (double(fs)/buffer_size);
            //cout << "How many times do we need to send messages: " << num_messages  <<endl;

            //file size is less than 256
            FileRequest* fm = (FileRequest*) buf;
            if (num_messages == 1 )
            {
                //cout << "Inside if" <<endl;
                fm->offset = 0;
                fm->length = fs;
            }
            else
            {
                fm->length = buffer_size;//want to extract the max number of bytes from the file at a time
                fm->offset = 0;
            }
            __int64_t  last_count = fs - buffer_size* (num_messages-1);
            chan.cwrite(buf, size_total);
            char* ret_buf = new char[buffer_size];
            chan.cread(ret_buf,buffer_size);

            string outputfilepath = string("received/") + string(filename);
            FILE* fp = fopen(outputfilepath.c_str(),"wb");
            fwrite(ret_buf, 1, fm->length, fp);

            struct timeval start1, end1;
            gettimeofday(&start1, NULL);
            for (int i = 1; i < num_messages; i++)
            {
                //cout << "Inside for loop" <<endl;

                if (i == num_messages-1)
                {
                    //cout << fm->offset + buffer_size <<endl;
                    //cout <<"last chunk ";
                    //cout << last_count <<endl;
                    fm->length = last_count;
                    ret_buf = new char[last_count];
                    fm->offset +=buffer_size;
                    //cout << "HERE " << endl ;
                    chan.cwrite(buf, size_total);
                    chan.cread(ret_buf,buffer_size);
                    fwrite(ret_buf, 1, fm->length, fp);
                }
                else
                {
                    //count += new_buff_capacity;
                    fm->offset +=buffer_size;
                    //cout << "HERE " << endl ;
                    chan.cwrite(buf, size_total);
                    chan.cread(ret_buf,buffer_size);
                    fwrite(ret_buf, 1, fm->length, fp);

                }
                //count += new_buff_capacity;

            }

            delete [] ret_buf;
            delete [] buf;



	// closing the channel
    Request q (QUIT_REQ_TYPE);
    chan.cwrite (&q, sizeof (Request));
	// client waiting for the server process, which is the child, to terminate
	wait(0);
	cout << "Client process exited" << endl;

}
