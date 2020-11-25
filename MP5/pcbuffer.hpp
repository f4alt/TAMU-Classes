/*
    File: pcbuffer.hpp
    Author: R. Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 2020/09/27
*/

#ifndef _pcbuffer_H_                   // include file only once
#define _pcbuffer_H_

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/
#include <pthread.h>
#include <queue>
#include <string>
#include "semaphore.hpp"

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
/* CLASS Response  */
/*--------------------------------------------------------------------------*/
class Response{
  public:

    string res;      // string server response
    int id;          // int client id

    Response(string s, int i);
};

/*--------------------------------------------------------------------------*/
/* CLASS   bounded P C B u f f e r  */
/*--------------------------------------------------------------------------*/
class PCBuffer {
  private:
    int size;
    queue<Response> q;

    Semaphore * lock;
    Semaphore * full;
    Semaphore * empty;

  public:
   PCBuffer(int _size);
   ~PCBuffer();

   void Deposit(Response _response);
   Response Retrieve();
};

#endif
