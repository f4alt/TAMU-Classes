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


	Semaphore* fullSlots;
	Semaphore* emptySlots;
	mutex m;
	// condition_variable data_available;	// for waiting on pop, signaled by push
	// condition_variable slot_available;	// waited on by push, signaled after popping


public:
	BoundedBuffer(int _cap){
		cap = _cap;

		fullSlots = new Semaphore(0);
		emptySlots = new Semaphore(_cap);
	}
	~BoundedBuffer(){
		delete fullSlots;
		delete emptySlots;
	}

	void push(vector<char> data){

		emptySlots->P();
		m.lock();
		q.push(data);
		m.unlock();
		fullSlots->V();


		// THIS WORKS
		// // vector<char> d (data, data + len);
		// unique_lock<mutex> l(m);
		// slot_available.wait(l, [this]{return q.size() < cap;});
		// // q.push(d);
		// q.push(data);
		// l.unlock();
		// data_available.notify_one();
	}

	vector<char> pop(){

		fullSlots->P();
		m.lock();
		vector<char> d = q.front();
		q.pop();
		m.unlock();
		emptySlots->V();

		return d;


		// THIS WORKS
		// unique_lock<mutex> l (m);
		// data_available.wait(l, [this]{return q.size() > 0;});
		// vector<char> d = q.front();
		// q.pop();
		// l.unlock();
		// // memcpy(buf, d.data(), d.size());
		// slot_available.notify_one();
		//
		// return d;
	}
};

#endif /* BoundedBuffer_ */
