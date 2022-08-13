/*
 File: my_allocator.cpp

 Author: Christopher McGregor
 Department of Computer Science
 Texas A&M University
 Date  : 08/30/20

 Modified:

 This file contains the implementation of the class MyAllocator.

 */

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <cstdlib>
#include "my_allocator.hpp"
#include <assert.h>
#include <iostream>

/*--------------------------------------------------------------------------*/
/* NAME SPACES */
/*--------------------------------------------------------------------------*/

using namespace std;
/* I know, it's a bad habit, but this is a tiny program anyway... */

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
/* FUNCTIONS FOR CLASS MyAllocator */
/*--------------------------------------------------------------------------*/

MyAllocator::MyAllocator(size_t _basic_block_size, size_t _size) {
  this->size_remaining = _size; // set total size_remaining of allocator
  this->start = std::malloc(_size); // set start pointer
  this->curr = (char*)(this->start); //typecast curr pointer to be used
}

MyAllocator::~MyAllocator() {
    // Same here...
}

void* MyAllocator::Malloc(size_t _length) {
    if(_length >= this->size_remaining) { // check if theres enough memory left
      cout << "not enough" << endl;
      return NULL;
    } else {
      void* result = (void*)this->curr; // save where the curr pointer is to return
      this->size_remaining -= _length; // decrement remaining memory amount
      this->curr += _length; // increment the current pointer
      return result; // return where the current pointer was
    }
}

bool MyAllocator::Free(void* _a) {
    // This empty implementation just uses C standard library free
    cout << "MyAllocator::Free called" << endl;
    // std::free(_a);
    return true;
}
