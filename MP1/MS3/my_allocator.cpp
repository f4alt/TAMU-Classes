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
  size_t remaining_total = _size;
  size = 0;
  block_size = _basic_block_size;

  this->start = std::malloc(_size);

  while (remaining_total > _basic_block_size) {
    int array_size = 0;
    while ((Fib(array_size) * _basic_block_size) < remaining_total) {
      array_size++;
    }
    if (size == 0) {
      list = new FreeList[array_size];
      size = array_size-2;
    }

    SegmentHeader* seg = new SegmentHeader(Fib(array_size - 2) * _basic_block_size);
    list[array_size - 2].Add(seg);
    remaining_total -= Fib(array_size - 1) * _basic_block_size;

    // cout << remaining_total << endl;
  }


  if (remaining_total == _basic_block_size) {
    SegmentHeader* seg = new SegmentHeader(_basic_block_size);
    list[0].Add(seg);
  }
  for (int i = 0; i <= size; i++) {
    list[i].expected_capacity = Fib(i+1) * block_size;
  }

  total_size = _size;
  //
  // for (int i = 0; i <= size; i++) {
  //   cout << "pos " << i << " size:" << list[i].list_size << " quantity:" << list[i].expected_capacity << endl;
  // }
}

MyAllocator::~MyAllocator() {
  // ?                  **************************************************************
}

void* MyAllocator::Malloc(size_t _length) {
<<<<<<< HEAD
  // round up to next multiple of blocksize
  size_t len = ((block_size + (_length + sizeof(SegmentHeader)) - 1) / block_size) * block_size;

  // find right size list
  int idx = 0;
  while (!sizeof(list) && (list[idx].empty() || list[idx].head->length < len)) { //******************* F(idx)??
    idx++;
  }

  // remove found segment from freelist
  seg = list[idx].Remove()
  if (seg.length == len) {
    // success? Now what                                                    ***************
    is_free = false;
  } else {

  }




  // OLD CODE
  SegmentHeader* seg = list.Head();
  while (seg != NULL && seg->length < len) {  // iterate until list is exhausted or we find something
    seg = seg->next;
=======
  size_t round_up;
  for (int i = 1;;i++) {
    round_up = Fib(i) * block_size;
    if (round_up >= _length + sizeof(SegmentHeader)) {
      break;
    }
>>>>>>> 2902862357a6fe51a4a720cc186f38b34ae70cc0
  }
  if (round_up == 0) {
    round_up = block_size;
  }
  if (round_up > total_size) {
    cout << "Error, cant allocate more - I didn't finish Coalesce() :(" << endl;
    exit(1);
  }

  while(true) {
    int i = 0;
    while(list[i].list_size == 0 || (Fib(i) * block_size) <= round_up) {
      // if (found) {
      //   break;
      // }
      // if (list[i].head != NULL) {
      //   if (list[i].head->length == round_up) {
      //     found = true;
      //     continue;
      //   }
      // }
      i++;
    }
    // cout << "i:" << i << endl;

    SegmentHeader *seg = list[i].head;

    // cout << "looking for:" << round_up << " expected_capacity: " << list[i].expected_capacity << endl;
    if (list[i].head->length == round_up || round_up == block_size) {
      // cout << "found" << endl;
      void* ptr = (void*)(list[i].head + sizeof(SegmentHeader));    // **************
      return ptr;
    } else { // split into buddies
      // cout << "split" << round_up << endl;
      SegmentHeader* SmallerBud = list[i].head->Split(Fib(i-1)*block_size);
      list[i - 1].Add(list[i].head);
      list[i - 2].Add(SmallerBud);
      list[i].Remove(seg);
    }

    // for (int i = 0; i <= size; i++) {
    //   cout << "pos " << i << " size:" << list[i].list_size << " quantity:" << list[i].expected_capacity << endl;
    // }
  }
  // for (int i = 0; i <= size; i++) {
  //   cout << "pos " << i << " size:" << list[i].list_size << " quantity:" << list[i].expected_capacity << endl;
  // }
}

bool MyAllocator::Free(void* _a) {
    // add segment back to free list
    SegmentHeader* seg = (SegmentHeader*)((char*)_a - sizeof(SegmentHeader));
    // list.Add(seg);
    return true;
}

SegmentHeader* MyAllocator::Coalesce(SegmentHeader* seg) {

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
