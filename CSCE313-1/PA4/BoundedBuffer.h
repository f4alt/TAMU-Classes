#ifndef BoundedBuffer_h
#define BoundedBuffer_h

#include <stdio.h>
#include <queue>
#include <string>
#include "Semaphore.h"
#include <thread>
#include <mutex>
#include <assert.h>

using namespace std;

class BoundedBuffer
{
private:
	int cap; // max number of items in the buffer
	queue<vector<char>> q;	/* the queue of items in the buffer. Note
	that each item a sequence of characters that is best represented by a vector<char> because:
	1. An STL std::string cannot keep binary/non-printables
	2. The other alternative is keeping a char* for the sequence and an integer length (i.e., the items can be of variable length), which is more complicated.*/

	// add necessary synchronization variables (e.g., sempahores, mutexes) and variables
	// Semaphore* lock;
	// Semaphore* full;
	// Semaphore* empty;
	mutex m;
	condition_variable data_avail;
	condition_variable slot_avail;


public:
	BoundedBuffer(int _cap){
		cap = _cap;
		// lock = new Semaphore(1);
	  // full = new Semaphore(0);
	  // empty = new Semaphore(cap);
		slot_avail.notify_all();
	}
	~BoundedBuffer(){
		// delete lock;
	  // delete full;
	  // delete empty;
	}

	void push(char* data, int len){
		// follow the class lecture pseudocode

		//1. Perform necessary waiting (by calling wait on the right semaphores and mutexes),
		// unique_lock<mutex> l (m);
		// slot_avail.wait(l, [this]{return q.size() < cap;});
		// empty->P();
		// lock->P();
		//2. Push the data onto the queue
		vector<char> d (data, data + len);
		q.push(d);
		// l.unlock();
		//3. Do necessary unlocking and notification
		// data_avail.notify_one();
		// lock->V();
		// full->V();
	}

	vector<char> pop(){
		//1. Wait using the correct sync variables
		// unique_lock<mutex> l (m);
		// data_avail.wait(l, [this]{return q.size() > 0;});
		// full->P();
		// lock->P();
		//2. Pop the front item of the queue.
		vector<char> d = q.front();
		q.pop();
		//3. Unlock and notify using the right sync variables
		// l.unlock();
		// slot_avail.notify_one();
		// lock->V();
		// empty->V();
		//4. Return the popped vector
		return d;
	}
};

#endif /* BoundedBuffer_ */
