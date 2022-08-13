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
  this->total_size = _size; // set total size_remaining of allocator
  this->block_size = _basic_block_size;
  this->start = std::malloc(_size);

  // create new segment header with size = entire available and add to free list
  SegmentHeader* seg1 = new(this->start)SegmentHeader(_size);
  this->list.Add(seg1);
}

MyAllocator::~MyAllocator() {
  // ?                  **************************************************************
}

void* MyAllocator::Malloc(size_t _length) {
  // round up to next multiple of blocksize
  size_t len = ((block_size + (_length + sizeof(SegmentHeader)) - 1) / block_size) * block_size;
  SegmentHeader* seg = list.Head();
  while (seg != NULL && seg->length < len) {  // iterate until list is exhausted or we find something
    seg = seg->next;
  }
  if (seg == NULL) { // Didn't find valid segment
    return NULL;
  }
  list.Remove(seg); // found valid segment, segment is no longer free
  if (seg->length > len) {
    SegmentHeader* seg2 = seg->Split(len);
    list.Add(seg2);
  }

  // return new starting point
  void* ptr = (void*)((char*)seg + sizeof(SegmentHeader));
  return ptr;
}

bool MyAllocator::Free(void* _a) {
    // add segment back to free list
    SegmentHeader* seg = (SegmentHeader*)((char*)_a - sizeof(SegmentHeader));
    return list.Add(seg);
    return true;
}
