/*
    File: pcbuffer.hpp

    Author: R. Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 2020/09/27

*/
#include "pcbuffer.hpp"
using namespace std;

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
int PCBuffer::Deposit(string _item) {
  empty->P();
  lock->P();
  q.push(_item);
  lock->V();
  full->V();
}

string PCBuffer::Retrieve() {
  full->P();
  lock->P();
  string r = q.front();
  q.pop();
  lock->V();
  empty->V();
  return r;
}
