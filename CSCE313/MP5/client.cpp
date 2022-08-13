/*
    File: client.cpp

    Author: C. McGregor
            Department of Computer Science
            Texas A&M University
    Date  :

    Client main program for MP5 in CSCE 313
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
#include <sys/time.h>
#include <errno.h>
#include <unistd.h>
#include <thread>
#include <iomanip>
#include <stdlib.h>

#include "netreqchannel.hpp"
#include "pcbuffer.hpp"

using namespace std;
/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLES */
/*--------------------------------------------------------------------------*/

// intake defaults
int b=10;
int w=20;
int n=30;
string hostName = "localHost";
int port = 8080;

// histogram vectors
vector<int> joe_histogram(100);
vector<int> jane_histogram(100);
vector<int> john_histogram(100);

// main buffer and stat buffers
PCBuffer* buffer;
PCBuffer* joe_buf;
PCBuffer* jane_buf;
PCBuffer* john_buf;

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

// pointers for pthread_create arg to allow ownership
int* joe=new int(0);
int* jane=new int(1);
int* john=new int(2);

/*--------------------------------------------------------------------------*/
/* Helper and thread functions */
/*--------------------------------------------------------------------------*/

void histogram(vector<int> patient, string name) {
    vector<int> partials(10);
    for (int j=0; j<partials.size(); ++j) {
        for (int k=0; k<partials.size(); ++k) {
            partials[j] += patient[k + j * 10];
        }
    }
    cout << "\n    " << name << endl
    <<setw(7)<<"0-9"<<setw(7)<<"10-19"<<setw(7)<<"20-29"<<setw(7)<<"30-39"<<setw(7)<<"40-49"<<setw(7)<<"50-59"
    <<setw(7)<<"60-69"<<setw(7)<<"70-79"<<setw(7)<<"80-89"<<setw(7)<<"90-99"<<endl<<endl;

    for (int i=0;i<10;++i) {
      cout << setw(7) << partials[i];
    }
    cout << endl << endl;
}

void* request_thread_fnct(void* person_id) {
    int req_id = *((int*)person_id);
    for(int i = 0; i < n; i++) {
        Response* r = new Response("temp",req_id);
        if (req_id == 0) {
            r->res = "data Joe Smith";
            r->id = 0;
        }
        else if (req_id == 1) {
            r->res = "data Jane Smith";
            r->id = 1;
        }
        else if (req_id == 2) {
            r->res = "data John Doe";
            r->id = 2;
        }

        buffer->Deposit(*r);
        delete r;
    }
}

void* event_thread_fnct(void* c) {
    NetworkRequestChannel* channels[w];
    int person_id[w];
    fd_set readset;
    int max = 0;
    int sel_result;
    Response r = Response("", 0);
    int wcount = 0;
    int rcount = 0;
    struct timeval te = {0,10};

    // create w threads and initialize person_id array
    for(int i = 0; i < w; i++) {
        channels[i] = new NetworkRequestChannel(hostName, port);
        person_id[i] = -1;
    }

    // fill all the channels with requests before trying to read from them
    for(int i = 0; i < w; i++) {
        r = buffer->Retrieve();
        wcount++;
        channels[i]->cwrite(r.res);
        person_id[i] = r.id;
    }

    while (1) {
        FD_ZERO(&readset);
        for(int i=0; i<w; i++) {
            if(channels[i]->read_fd() > max) {
                max = channels[i]->read_fd();
            }
            FD_SET(channels[i]->read_fd(), &readset);
        }

        sel_result = select(max+1, &readset, NULL, NULL, &te);

        if (sel_result) {
            for(int i=0; i < w; i++) {
                if(FD_ISSET(channels[i]->read_fd(), &readset)) {
                    string serv_resp = channels[i]->cread();
                    rcount++;
                    switch (person_id[i]) {
                    case 0:
                        joe_buf->Deposit(Response(serv_resp, 0));
                        break;
                    case 1:
                        jane_buf->Deposit(Response(serv_resp, 1));
                        break;
                    case 2:
                        john_buf->Deposit(Response(serv_resp, 2));
                        break;
                    }

                    // only write what is available to avoid deadlock
                    if(wcount < n * 3) {
                        r = buffer->Retrieve();
                        wcount++;
                        channels[i]->cwrite(r.res);
                        person_id[i] = r.id;
                    }
                }
            }
        }

        // break condition
        if (rcount == n * 3) {
            break;
        }
    }

    // close request channels
    for(int i=0; i < w; i++) {
        channels[i]->cwrite("quit");
    }
}

void* stat_thread_fnct(void* person_id) {
    int req_id = *((int*)person_id);
    Response r("temp",-1);

    for(int i = 0; i < n; i++) {
        if (req_id==0) {
            r = joe_buf->Retrieve();
            joe_histogram[atoi(r.res.c_str())]+=1;
        }
        else if (req_id == 1) {
            r = jane_buf->Retrieve();
            jane_histogram[atoi(r.res.c_str())]+=1;
        }
        else if (req_id==2) {
            r = john_buf->Retrieve();
            john_histogram[atoi(r.res.c_str())]+=1;
        }
    }
}


/*--------------------------------------------------------------------------*/
/* MAIN FUNCTION */
/*--------------------------------------------------------------------------*/

int main(int argc, char * argv[]) {
    // take in n(umber of data req), b(uffer size), w( req channels),
    // hostName, port from command line
    int option = 0;
    string temp;
    while((option = getopt (argc, argv, "n:w:b:p:h:")) != -1)
        switch (option) {
        case 'n':
            n=atoi(optarg);
            break;
        case 'w':
            w=atoi(optarg);
            break;
        case 'b':
            b=atoi(optarg);
            break;
        case 'p':
            port = atoi(optarg);
            break;
        case 'h':
            temp = optarg;
            if (temp != "") {
              hostName = temp;
            }
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
            cout<<"cmd line error\n";
            abort();
        }

    // main buffer and stat buffers
    buffer = new PCBuffer(b);
    joe_buf = new PCBuffer(b);
    jane_buf = new PCBuffer(b);
    john_buf = new PCBuffer(b);

    // create request threads (one per person)
    pthread_t request_threads[3];
    pthread_create(&request_threads[0], NULL, request_thread_fnct, (void*)joe);
    pthread_create(&request_threads[1], NULL, request_thread_fnct, (void*)jane);
    pthread_create(&request_threads[2], NULL, request_thread_fnct, (void*)john);

    // create event handler thread
    pthread_t event_handler;
    pthread_create(&event_handler, NULL, event_thread_fnct, NULL);

    // create stat threads (one per person for histograms)
    pthread_t stat_threads[3];
    pthread_create(&stat_threads[0], NULL, stat_thread_fnct, (void*)joe);
    pthread_create(&stat_threads[1], NULL, stat_thread_fnct, (void*)jane);
    pthread_create(&stat_threads[2], NULL, stat_thread_fnct, (void*)john);

    // get start time
    timeval start, end;
    gettimeofday(&start, NULL);

    // join all req threads
    pthread_join(request_threads[0],NULL);
    pthread_join(request_threads[1], NULL);
    pthread_join(request_threads[2], NULL);

    // join event thread
    pthread_join(event_handler,NULL); //wait for event handler to finish

    // join stat threads
    pthread_join(stat_threads[0], NULL); // wait for stat threads to exit
    pthread_join(stat_threads[1], NULL);
    pthread_join(stat_threads[2], NULL);

    // get end time
    gettimeofday(&end,NULL);

    // pause to make sure all threads have terminated
    sleep(1);

    // output each patients histogram and elapsed time
    histogram(joe_histogram, "Joe Smith");
    histogram(jane_histogram, "Jane Smith");
    histogram(john_histogram, "John Doe");
    cout << "Total requests: " << n * 3 << endl;
    int secs = (end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)/(int) 1e6;
    int usecs = (int)(end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)%((int) 1e6);
    cout << "Took " << secs << " seconds and " << usecs << " micro seconds" << endl << endl;

    return 0;
}
