/*
    File: free_list.cpp

    Author: Christopher McGregor
            Department of Computer Science
            Texas A&M University
    Date  : Sept 9, 2020

    Modified:

    This file contains the implementation of the class FreeList.

*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <iostream>
#include "free_list.hpp"
#include <cassert>

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
/* FUNCTIONS FOR CLASS SegmentHeader */
/*--------------------------------------------------------------------------*/

SegmentHeader::SegmentHeader(size_t _length, bool _is_free) {
  length = _length;
  is_free = _is_free;
  cookie = COOKIE_VALUE;
  next = NULL;
  prev = NULL;
}

SegmentHeader::~SegmentHeader() {
  // You may need to add code here.
}


void SegmentHeader::CheckValid() {
  if (cookie != COOKIE_VALUE) {
    cout << "INVALID SEGMENT HEADER!!" << endl;
    assert(false);
    // You will need to check with the debugger to see how we got into this
    // predicament.
  }
}

SegmentHeader* SegmentHeader::Split(size_t _len) {
  SegmentHeader* seg_new = new((void*)((char*)this + _len))SegmentHeader(this->length - _len);
  this->length = _len;
  return seg_new;
}

/*--------------------------------------------------------------------------*/
/* FUNCTIONS FOR CLASS FreeList */
/*--------------------------------------------------------------------------*/

FreeList::FreeList() {
  this->head=NULL;
  this->tail=NULL;
  this->list_size=0;
}

FreeList::~FreeList() {
  // You may need to add code here.
}

bool FreeList::Add(SegmentHeader * _segment) {
  if (this->head == NULL) {                     // empty list
    this->head = _segment;
    this->tail = this->head;
  } else {                                      // else push to front
    this->head->prev = _segment;
    _segment->next = this->head;
    this->head = _segment;
  }

  _segment->is_free = true;                     // update is_free and size
  this->list_size++;
  return true;
}

bool FreeList::Remove(SegmentHeader * _segment) {
  if (this->head == _segment) {                 // check if to be removed is head
    this->head = _segment->next;
  }
  else if (this->tail == _segment) {            // check if to be removed is tail
    this->tail = _segment->prev;
  } else {
    _segment->prev->next = _segment->next;
    _segment->next->prev = _segment->prev;
  }

  _segment->is_free = false;                    // update is_free and list size
  this->list_size--;
  return true;
}

int FreeList::Size() {
  return this->list_size;
}

SegmentHeader* FreeList::Head() {
  return this->head;
}

SegmentHeader* FreeList::Tail() {
  return this->tail;
}

void FreeList::PrintList() {
  SegmentHeader* temp = this->head;
  for(int i = 0; i < this->list_size; ++i) {
    cout << temp << "->";
    temp = temp->next;
  }
  cout << endl;
}
