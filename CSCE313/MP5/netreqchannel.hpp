/*
    File: netreqchannel.hpp

    Author: R. Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 2019/11/19

*/

#ifndef _netreqchannel_HPP_                   // include file only once
#define _netreqchannel_HPP_

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

//#include <iostream>
//#include <fstream>

#include <string>

using namespace std;

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CLASS  N e t w o r k R e q u e s t C h a n n e l */
/*--------------------------------------------------------------------------*/

class NetworkRequestChannel {

private:

  int fd; // socket file descriptor;

public:

  /* -- CONSTRUCTOR/DESTRUCTOR */

  // client side
  NetworkRequestChannel(const string _server_host_name, const unsigned short _port_no);
  /* Creates a CLIENT-SIDE local copy of the channel. The channel is connected
     to the given port number at the given server host.
     THIS CONSTRUCTOR IS CALLED BY THE CLIENT. */

  // ********************************************************************************
  // Here we need to add an additional backlog parameter to allow the dataserver listen
  // Additionally, in order to use pthread_create we need the start routine (in our
  // case connection_handler) to be of the form "void * (*start_routine) (void *)"
  // instead of "void * (*connection_handler) (int *)
  // ********************************************************************************
  NetworkRequestChannel(const unsigned short _port_no, void * (*connection_handler) (void *), int backlog);
  /* Creates a SERVER-SIDE local copy of the channel that is accepting connections
     at the given port number.
     NOTE that multiple clients can be connected to the same server-side end of the
     request channel. Whenever a new connection comes in, it is accepted by the
     the server, and the given connection handler is invoked. The parameter to
     the connection handler is the file descriptor of the slave socket returned
     by the accept call.
     NOTE that it is up to the connection handler to close the socket when the
     client is done. */

  ~NetworkRequestChannel();
  /* Destructor of the local copy of the bus. By default, the Server Side deletes
     any IPC mechanisms associated with the channel. */

  string send_request(string _request);
  /* Send a string over the channel and wait for a reply. */

  string cread();
  /* Blocking read of data from the channel. Returns a string of characters
     read from the channel. Returns NULL if read failed. */

  int cwrite(string _msg);
  /* Write the data to the channel. The function returns the number of characters written
     to the channel. */

  int read_fd();
};


#endif
