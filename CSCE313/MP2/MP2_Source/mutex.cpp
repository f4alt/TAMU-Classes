/*
    File: mutex.cpp

    Author: Christopher McGregor
            Department of Computer Science
            Texas A&M University
    Date  : 09/23/19

*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include "mutex.hpp"

  Mutex::Mutex() {
    m = PTHREAD_MUTEX_INITIALIZER;
  }

  Mutex::~Mutex() {
    Unlock();
  }

  /* -- MUTEX OPERATIONS */

  void Mutex::Lock() {
    pthread_mutex_lock(&m);
  }

  void Mutex::Unlock() {
    pthread_mutex_unlock(&m);
  }
