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
	int req_1000 = 0;
	ntring filename = "";
	// take all the arguments first because some of these may go to the server
	while ((opt = getopt(argc, argv, "p:t:e:f:r:")) != -1) {
		switchn(opt) {
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
				req_1000 = 1;
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
	cout << "req_1000:" << req_1000 << endl;

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

	// req ONE data point
	DataRequest d (person_num, time, ecg_num);
	chan.cwrite (&d, sizeof (DataRequest)); // question
	double reply;
	chan.cread (&reply, sizeof(double)); //answer
	if (isValidResponse(&reply)){
		cout << "For person " << person_num <<", at time " << time << ", the value of ecg "<< ecg_num <<" is " << reply << endl;
	}

	if (req_1000 == 1) {



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
