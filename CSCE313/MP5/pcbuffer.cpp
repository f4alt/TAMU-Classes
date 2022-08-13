/*
    File: pcbuffer.hpp
    Author: C. McGregor
            Department of Computer Science
            Texas A&M University
    Date  : 2020/09/27
*/

#include "pcbuffer.hpp"
using namespace std;

// ************** Response ****************** //
/* CONSTRUCTOR */
Response::Response(string s, int i) {
  res = s;
  id = i;
}

// ************** PCBuffer ****************** //
/* -- CONSTRUCTOR/DESTRUCTOR */
PCBuffer::PCBuffer(int _size) {
  size = _size;
  lock = new Semaphore(1);
  full = new Semaphore(0);
  empty = new Semaphore(size);
}

PCBuffer::~PCBuffer() {
  delete lock;
  delete full;
  delete empty;
}

/* -- OPERATIONS ON PC BUFFER */
void PCBuffer::Deposit(Response _response) {
  empty->P();
  lock->P();
  q.push(_response);
  lock->V();
  full->V();
}

Response PCBuffer::Retrieve() {
  full->P();
  lock->P();
  Response r=q.front();
  q.pop();
  lock->V();
  empty->V();
  return r;
}
