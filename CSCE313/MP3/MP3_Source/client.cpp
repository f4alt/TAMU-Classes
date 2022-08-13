/*
    File: simpleclient.C

    Author: R. Bettati
            Department of Computer Science
            Texas A&M University
    Date  :

    Simple client main program for MPs in CSCE 313
*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <cassert>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>

#include <errno.h>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <iomanip>

#include "reqchannel.hpp"
#include "pcbuffer.hpp"

using namespace std;

/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLES */
/*--------------------------------------------------------------------------*/

string patient_names[] = {"Joe Smith", "Jane Smith", "John Doe" };
int patient_amt = 3;

vector<int> joe_histogram(100); //histogram
vector<int> jane_histogram(100);//100 spots for each possible number
vector<int> john_histogram(100);

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* MAIN FUNCTION */
/*--------------------------------------------------------------------------*/
RequestChannel* create_chan(RequestChannel* req) {
  string name = req->send_request("newthread");
  RequestChannel* req2 = new RequestChannel(name, RequestChannel::Side::CLIENT);
  return req2;
}

void patient_thread_fnct(int n, int pat_num, PCBuffer* buffer) {
  for (int i = 0; i < n; i++) {
    buffer->Deposit("data " + patient_names[pat_num]);
  }
}

void stat_thread_fnct(int req_id, string r) {
  if (req_id == 0) {
      joe_histogram[atoi(r.c_str())]+=1;
  } else if (req_id == 1){
      jane_histogram[atoi(r.c_str())]+=1;
  } else if (req_id == 2) {
      john_histogram[atoi(r.c_str())]+=1;
  }
}

void workers_thread_fnct(RequestChannel* req_chan, PCBuffer* req_buf) {
  while(1) {
    string req = req_buf->Retrieve();
    string r = req_chan->send_request(req);
    thread stat_thread;

    if (req == "data Joe Smith") {
        stat_thread = thread(stat_thread_fnct, 0, r);
        stat_thread.join();
    } else if (req == "data Jane Smith"){
        stat_thread = thread(stat_thread_fnct, 1, r);
        stat_thread.join();
    } else if (req == "data John Doe") {
        stat_thread = thread(stat_thread_fnct, 2, r);
        stat_thread.join();
    }

    if (req == "quit") {
      delete req_chan;
      break;
    }
  }
}

void histogram(vector<int> patient, string name) {
    vector<int> partials(10);
    for (int j=0; j<partials.size();++j) {
        for (int k=0;k<partials.size();++k) {
            partials[j]+=patient[k+j*10];
        }
    }
    cout<<"\n    "<<name<<endl
    <<setw(7)<<"0-9"<<setw(7)<<"10-19"<<setw(7)<<"20-29"<<setw(7)<<"30-39"<<setw(7)<<"40-49"<<setw(7)<<"50-59"
    <<setw(7)<<"60-69"<<setw(7)<<"70-79"<<setw(7)<<"80-89"<<setw(7)<<"90-99"<<endl<<endl;

    for (int i=0;i<10;++i){
      cout<<setw(7)<<partials[i];
    }
    cout<<endl<<endl;
}

int main(int argc, char * argv[]) {
  // TAKE IN n, b, w from command line // ***********************
  int b = 10;
  int w = 20;
  int n = 30;
  int option;

  while ((option = getopt (argc, argv, "n:b:w:")) != -1)
    switch (option)
      {
      case 'n':
        n = stoi(optarg);
        break;
      case 'b':
        b = stoi(optarg);
        break;
      case 'w':
        w = stoi(optarg);
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

  // fork
  pid_t pid = fork();
  if (pid == -1) {
    exit(0);
  }
  if (pid == 0) {
    execv("dataserver", NULL);
  }

  // make buffer
  PCBuffer buffer(b);

  // make req chan and send w
  RequestChannel* chan = new RequestChannel("control", RequestChannel::Side::CLIENT);
  RequestChannel* wor_chan[w];

  // get start time
  timeval start, end;
  gettimeofday(&start, NULL);

  // create channel for each worker thread
  for (int i = 0; i < w; i++) {
    wor_chan[i] = create_chan(chan);
  }

  // assign patient threads
  thread patients[patient_amt];
  for (int i = 0; i < patient_amt; i++) {
    patients[i] = thread(patient_thread_fnct, n, i, &buffer);
  }

  // assign worker threads
  thread workers[w];
  for (int i = 0; i < w; i++) {
    workers[i] = thread(workers_thread_fnct, wor_chan[i], &buffer);
  }

  // join patient threads
  for (int i = 0; i < patient_amt; i++) {
    patients[i].join();
  }

  // kill worker channels
  for (int i = 0; i < w; i++) {
    buffer.Deposit("quit");
  }

  // join worker threads
  for (int i = 0; i < w; i++) {
    workers[i].join();
  }

  // mark end time
  gettimeofday(&end, NULL);

  // send quit message for control channel
  chan->send_request("quit");

  // wait to make sure all threads have terminated
  wait(0);

  // output each patients histogram and total elapsed time
  histogram(joe_histogram, "Joe Smith");
  histogram(jane_histogram, "Jane Smith");
  histogram(john_histogram, "John Doe");
  int secs = (end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)/(int) 1e6;
    int usecs = (int)(end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)%((int) 1e6);
    cout << "Took " << secs << " seconds and " << usecs << " micro seconds" << endl;
}
