/*
    File: my_allocator.hpp

    Author: Christopher McGregor
            Department of Computer Science and Engineering
            Texas A&M University
    Date  : 08/30/20

    Modified:

*/

#ifndef _my_allocator_hpp_                   // include file only once
#define _my_allocator_hpp_

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <cstdlib>
#include <vector>
#include <unistd.h>
#include "free_list.hpp"

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CLASS   MyAllocator */
/*--------------------------------------------------------------------------*/

class MyAllocator {

 private:
   size_t total_size; // overall available size
   size_t block_size; // basic block size of memory space
   void* start; // beginning of allocated memory space
   FreeList* list;
   size_t size;

 public:
  MyAllocator(size_t _basic_block_size, size_t _size);
  /* This function initializes the memory allocator and makes a portion of
     ’_size’ bytes available. The allocator uses a ’_basic_block_size’ as
     its minimal unit of allocation.
     NOTE: In the old days one used 'unsigned int' for the size. The C
     Standards Committee has added the 'size_t' data type to ensure to
     represent memory sizes. This makes the code more portable. Depending
     on the architecture, 'size_t' may or may not be the same
     as 'unsigned int'.
  */

  ~MyAllocator();
  /* This function returns any allocated memory to the operating system.
  */

  void* Malloc(size_t _length);
  /* Allocate _length number of bytes of free memory and returns the
     address of the allocated portion. Returns nullptr when out of memory.
  */

  bool Free(void* _a);
  /* Frees the section of physical memory previously allocated
     using ’Malloc’. Returns true if everything ok. */

  int Fib(int stop_pos);

  SegmentHeader* Coalesce(SegmentHeader* seg);
};

#endif
