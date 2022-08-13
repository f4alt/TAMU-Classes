/*
    File: dataserver.cpp

    Author: C. McGregor
            Department of Computer Science
            Texas A&M University
    Date  :

    Dataserver main program for MP5 in CSCE 313
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
#include <sstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#include "netreqchannel.hpp"

using namespace std;

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* VARIABLES */
/*--------------------------------------------------------------------------*/

const int MAX_MSG = 255;

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/
std::string int2string(int number) {
   std::stringstream ss;                  //create a stringstream
   ss << number;                          //add number to the stream
   return ss.str();                       //return a string with the contents of the stream
}

std::string generate_data() {
  // Generate the data to be returned to the client.
  usleep(1000 + (rand() % 5000));
  return int2string(rand() % 100);
}

string server_read(int* fd) {
	char buffer[MAX_MSG];

	read(*fd, buffer, MAX_MSG);             // read response into buffer
	string data = buffer;                   // convert char array to string and return
	return data;
}

void server_write(int* fd, string msg) {
  // Error checking for message length
	if(msg.length() >= MAX_MSG) {
		cerr << "ERROR: Message too large" << endl;
  }

  // check return val to ensure write
	if(write(*fd, msg.c_str(), msg.length()+1) < 0) {
		cerr << "ERROR: Server Write" << endl;
  }
}

void process_hello(int * fd, const string & _request) {
	server_write(fd, "hello to you too");
}

void process_data(int * fd, const string &  _request) {
  std::string data = generate_data();
  server_write(fd, data);
}

void process_request(int* fd, const string & _request) {
  if (_request.compare(0, 5, "hello") == 0) {
    process_hello(fd, _request);
  } else if (_request.compare(0, 4, "data") == 0) {
    process_data(fd, _request);
  } else {
    cerr << "ERROR: Unknown Request" << endl;
  }
}

void * connection_handler(void * arg) {
	int * fd = (int*)arg;

	if(fd == NULL) {
		cout << "ERROR: file descriptor is null" << endl;
  }

  cout << "New connection" << endl;

	while(1) {
		string request = server_read(fd);

		if (request.compare("quit") == 0) {
			server_write(fd, "bye");
			usleep(8000);                    // give the other end a bit of time.
			break;                           // break out of the loop;
		}

		process_request(fd, request);
	}

	cout << "Connection Closed" << endl;
}

/*--------------------------------------------------------------------------*/
/* MAIN FUNCTION */
/*--------------------------------------------------------------------------*/

int main(int argc, char * argv[]) {
  // default values
	int backLog=100;
	unsigned short port= 8080;

  // get command line inputs port and backlog
  int option = 0;
	while((option = getopt(argc, argv, "p:b:")) != -1) {
		switch(option){
			case 'p':
				port = atoi(optarg);
				break;
			case 'b':
				backLog = atoi(optarg);
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
	}

	cout << "SERVER STARTED ON PORT: " << port << endl;

	NetworkRequestChannel server(port, connection_handler, backLog);

	server.~NetworkRequestChannel();
}
