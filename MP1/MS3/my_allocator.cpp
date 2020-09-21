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
  size_t remaining_size = _size;
  block_size = _basic_block_size;

  this->start = std::malloc(_size);

  // find max fib quantity and set free_list size
  int array_size = 0;
  while ((Fib(array_size) * _basic_block_size) < _size) {
    array_size++;
  }
  list = new FreeList[array_size];

  SegmentHeader* seg = new SegmentHeader(Fib(array_size - 1) * _basic_block_size);
  list[array_size - 1].Add(seg);

  // for (int i = 0; i < array_size; i++) {
  //   list[i].expected_capacity = Fib(i+1) * block_size;
  //   cout << list[i].list_size << endl;
  //   cout << list[i].expected_capacity << endl;
  // }
}

MyAllocator::~MyAllocator() {
  // ?                  **************************************************************
}

void* MyAllocator::Malloc(size_t _length) {
  size_t round_up;
  for (int i = 1;;i++) {
    round_up = Fib(i) * block_size;
    if (round_up >= _length + sizeof(SegmentHeader)) {
      break;
    }
  }

  int i = 0;
  while(i <= sizeof(list)) {
    cout << "i:" << i << " expected cap:" << list[i].expected_capacity << " round up:" << round_up << endl;
    if(list[i].head == NULL || round_up > Fib(i)) {
      i++;
    }

    if (list[i].expected_capacity == round_up) {
      void* ptr = (void*)(list[i].head + sizeof(SegmentHeader));    // **************
      return ptr;
    }
    else { // split into buddies
      SegmentHeader* SmallerBud = list[i].head->Split(round_up);
      list[i - 2].Add(SmallerBud);
      list[i - 1].Add(list[i].head);
      list[i].Remove(list[i].head);
    }
  }


  // OLD CODE
  // // round up to next multiple of blocksize
  // size_t len = ((block_size + (_length + sizeof(SegmentHeader)) - 1) / block_size) * block_size;
  // SegmentHeader* seg = list.Head();
  // while (seg != NULL && seg->length < len) {  // iterate until list is exhausted or we find something
  //   seg = seg->next;
  // }
  // if (seg == NULL) { // Didn't find valid segment
  //   return NULL;
  // }
  // list.Remove(seg); // found valid segment, segment is no longer free
  // if (seg->length > len) {
  //   SegmentHeader* seg2 = seg->Split(len);
  //   list.Add(seg2);
  // }
  //
  // // return new starting point
  // void* ptr = (void*)((char*)seg + sizeof(SegmentHeader));
  // return ptr;
}

bool MyAllocator::Free(void* _a) {
    // add segment back to free list
    SegmentHeader* seg = (SegmentHeader*)((char*)_a - sizeof(SegmentHeader));
    // list.Add(seg);
    return true;
}

int MyAllocator::Fib(int stop_pos) {
  int x = 1;
  int prev_x = 1;

  for (int i = 1; i < stop_pos; i++) {
    x += prev_x;
    prev_x = x - prev_x;
  }

  return x;
}
