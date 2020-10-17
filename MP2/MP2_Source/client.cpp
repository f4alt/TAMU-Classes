/*
    File: client.cpp

    Author: Christopher McGregor
            Department of Computer Science
            Texas A&M University
    Date  : 2020/09/28

    Simple client main program for MP2 in CSCE 313
*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <cassert>
#include <string>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <iomanip>
#include <cmath>
#include <limits>

#include "reqchannel.hpp"

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
/* FORWARDS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTIONS -- SUPPORT FUNCTIONS */
/*--------------------------------------------------------------------------*/

std::string int2string(int number) {
  std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

/*--------------------------------------------------------------------------*/
/* MAIN FUNCTION */
/*--------------------------------------------------------------------------*/
std::string generate_data() {
  // std::cout << "gen_data" << std::endl;
  return int2string(rand() % 100);
}

int main(int argc, char * argv[]) {
  pid_t pid = fork();
  if (pid == -1) {
    exit(0);
  }
  if (pid == 0) {
    // std::cout << "Child" << std::endl;
    execv("dataserver", NULL);
  }

  std::cout << "CLIENT STARTED:" << std::endl;

  std::cout << "Establishing control channel... " << std::flush;
  RequestChannel chan("control", RequestChannel::Side::CLIENT);
  std::cout << "done." << std::endl;

  // ********* PART TWO TIME DIFFERENCIAL *************
  // struct timeval start, end;
  // gettimeofday(&start, NULL);
  // std::string reply = chan.send_request("data Christopher McGregor");
  // chan.send_request(generate_data);
  // std::string a = chan.generate_data;
  // chan->generate_data;
  // std::string* return_data = &chan.send_request.generate_data;
  // gettimeofday(&end, NULL);
  // double time_taken;
  // std::cout<<"------------------------"<<std::endl;
  // time_taken = (end.tv_sec - start.tv_sec) * 1e6;
  // time_taken = (time_taken + (end.tv_usec -
  //                            start.tv_usec)) * 1e-6;
  //
  // std::cout << "Time taken:" << std::fixed << time_taken << std::setprecision(6);
  // std::cout << " sec" << std::endl;
  // string return_data = RequestChannel(generate_data());

  // ************  DEFAULT STUFF  *******************
  std::string reply1 = chan.send_request("hello");
  std::cout << "Reply to request 'hello' is '" << reply1 << "'" << std::endl;

  std::string reply2 = chan.send_request("data Joe Smith");
  std::cout << "Reply to request 'data Joe Smith' is '" << reply2 << "'" << std::endl;

  std::string reply3 = chan.send_request("data Jane Smith");
  std::cout << "Reply to request 'data Jane Smith' is '" << reply3 << "'" << std::endl;

  for(int i = 0; i < 100; i++) {
    std::string request_string("data TestPerson" + int2string(i));
    std::string reply_string = chan.send_request(request_string);
    std::cout << "reply to request " << i << ":" << reply_string << std::endl;;
  }

  std::string reply4 = chan.send_request("quit");
  std::cout << "Reply to request 'quit' is '" << reply4 << std::endl;

  usleep(1000000);
}
