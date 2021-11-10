#include <iostream>
#include <thread>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
#include "Semaphore.h"
using namespace std;

Sempahore adone(0);
Semaphore bdone(0);
Semaphore cdone(1);
mutex mtx;
int bcount = 0;

void A_thread() {
  while (1) {
    // caravan C signal
    cdone.P();

    // -- whatever A is supposed to do --

    // signal TWO since we want two B instances
    adone.V();
    adone.V();
  }
}

void B_thread() {
  while (1) {
    // caravan A signal
    adone.P();

    // -- whatever B is supposed to do --

    // lock to keep thread safe
    mtx.Lock();
    bcout++;
    if (bcount == 2) {  // two B instances done, signal
      bdone.V();
      bcount = 0;
    }
    mtx.Unlock();
  }
}

void C_thread() {
  // caravan B signal
  bdone.P();

  // -- whatever C is supposed to do --

  cdone.V();
}
