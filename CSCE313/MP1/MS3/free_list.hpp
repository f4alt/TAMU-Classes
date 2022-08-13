/*
    File: free_list.hpp

    Author: Christopher McGregor
            Department of Computer Science and Engineering
            Texas A&M University
    Date  : Sept 9, 2020

    Modified:

*/

#ifndef _free_list_hpp_                   // include file only once
#define _free_list_hpp_

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <cstdlib>

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */
/*--------------------------------------------------------------------------*/

class SegmentHeader {

private:
  static const unsigned COOKIE_VALUE = 0xBADB00;
  unsigned int cookie; /* To check whether this is a genuine header! */


public:
  SegmentHeader* next; // make getters/setters for next and prev!     ************************
  SegmentHeader* prev;
  size_t length;
  bool is_free;
  SegmentHeader(size_t _length, bool _is_free = true);

  ~SegmentHeader();
  /* We probably won't need the destructor. */

  void CheckValid();
  /* Check if the cookie is valid. */

  SegmentHeader* Split(size_t _len);

  // GETTERS
  size_t Length();
};

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CLASS  FreeList */
/*--------------------------------------------------------------------------*/
class FreeList {

 private:
<<<<<<< HEAD
   SegmentHeader* head;
   SegmentHeader* tail;
   int list_size;
   int list_capacity;
=======
>>>>>>> 2902862357a6fe51a4a720cc186f38b34ae70cc0

 public:
   size_t expected_capacity;
   int list_size;
   SegmentHeader* head;
   SegmentHeader* tail;
   
   FreeList();
   /* This function initializes a new free-list. */

   ~FreeList();
   /* We probably don't need a destructor. */

   bool Remove(SegmentHeader * _segment);
   /* Remove the given segment from the given free list.
     Returns true if the function succeeds. */

   bool Add(SegmentHeader * _segment);
   /* Add the segment to the given free list. */

   /* GETTER FUNCTIONS, AND FULL LIST PRINT FOR TESTING */
   int Size();
   SegmentHeader* Head();
   SegmentHeader* Tail();
   void PrintList();
};

#endif
