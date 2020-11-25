/*
    File: netreqchannel.cpp

    Author: C. McGregor
            Department of Computer Science
            Texas A&M University
    Date  :

    New ReqChannel main program for MP5 in CSCE 313
*/

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <string.h>
#include <sstream>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include "netreqchannel.hpp"

using namespace std;

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

const int MAX_MSG = 255;

NetworkRequestChannel::NetworkRequestChannel(const string _server_host_name, const unsigned short _port_no) {
  // convert port # to string
	stringstream ss;
	ss << _port_no;
	string port = ss.str();

	// set sockIn transport address
  struct sockaddr_in sockIn;
	memset(&sockIn, 0, sizeof(sockIn));
	sockIn.sin_family = AF_INET;

  // make port
	if(struct servent * pse = getservbyname(port.c_str(), "tcp")) {
		sockIn.sin_port = pse->s_port;
  } else if ((sockIn.sin_port = htons((unsigned short)atoi(port.c_str()))) == 0) {
		cerr << "ERROR: cant connect port" << endl;
  }

	if(struct hostent * hn = gethostbyname(_server_host_name.c_str())) {
		memcpy(&sockIn.sin_addr, hn->h_addr, hn->h_length);
  } else if((sockIn.sin_addr.s_addr = inet_addr(_server_host_name.c_str())) == INADDR_NONE) {
		cerr << "ERROR: cant determine host <" << _server_host_name << ">" << endl;
  }

  // verify socket connect
	int s = socket(AF_INET, SOCK_STREAM, 0);
	if(connect(s, (struct sockaddr *)&sockIn, sizeof(sockIn)) < 0) {
		cerr << "ERROR: cant connect to " << _server_host_name << ":" << port.c_str() << endl;
  }

  // set fd
  fd = s;
}

NetworkRequestChannel::NetworkRequestChannel(const unsigned short _port_no, void * (*connection_handler) (void *), int backlog) {
  // convert port # to string
  stringstream ss;
	ss << _port_no;
	string port = ss.str();

	struct sockaddr_in serverIn;
	memset(&serverIn, 0, sizeof(serverIn));
	serverIn.sin_family = AF_INET;
	serverIn.sin_addr.s_addr = INADDR_ANY;

	if(struct servent * pse = getservbyname(port.c_str(), "tcp")) {
		serverIn.sin_port = pse->s_port;
  } else if((serverIn.sin_port = htons((unsigned short)atoi(port.c_str()))) == 0) {
		cerr << "ERROR: can't get port" << endl;;
  }

	int socknum  = socket(AF_INET, SOCK_STREAM, 0);
	if(bind(socknum, (struct sockaddr *)&serverIn, sizeof(serverIn)) < 0) {
		cerr << "ERROR: can't bind" << endl;
  }

  // check for connections
	listen(socknum, backlog);

	int serverSize = sizeof(serverIn);

	while(1) {
		int * slave = new int;

		pthread_t thread;
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		*slave = accept(socknum,(struct sockaddr*)&serverIn, (socklen_t*)&serverSize);

		if(slave < 0) {
			delete slave;

			if(errno == EINTR) {
        continue;
      } else {
        cerr << "ERROR: in accept()\n";
      }
		}

		pthread_create(&thread, &attr, connection_handler, (void*)slave);
	}
}

NetworkRequestChannel::~NetworkRequestChannel() {
	close(fd);
}

string NetworkRequestChannel::cread() {
	char buffer[MAX_MSG];

	if (read(fd, buffer, MAX_MSG) < 0) {
		cerr << "ERROR: reading" << endl;
  }

	return (string)buffer;
}

int NetworkRequestChannel::cwrite(string _msg) {
  // error handling for msg size
	if (_msg.length() >= MAX_MSG) {
		cerr << "ERROR: Message too long" << endl;
		return -1;
	}

	const char * s = _msg.c_str();

	if (write(fd, s, strlen(s)+1) < 0) {
		cerr<<"ERROR: writing" << endl;
  }

  return _msg.length();
}

int NetworkRequestChannel::read_fd() {
	return fd;
}
