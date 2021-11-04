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
	mutex m;


public:
	BoundedBuffer(int _cap){
		cap = _cap;

	}
	~BoundedBuffer(){

	}

	void push(char* data, int len){
		// follow the class lecture pseudocode

		//1. Perform necessary waiting (by calling wait on the right semaphores and mutexes),
		m.lock();
		//2. Push the data onto the queue
		vector<char> d (data, data + len);
		q.push(d);
		//3. Do necessary unlocking and notification
		m.unlock();


	}

	vector<char> pop(char* buf, int bufcap){
		//1. Wait using the correct sync variables
		//2. Pop the front item of the queue.
		m.lock();
		vector<char> d = q.front();
		q.pop();
		m.unlock();
		//3. Unlock and notify using the right sync variables
		//4. Return the popped vector
		assert(d.size() <= bufcap);
		memcpy(buf, d.data(), d.size());
	}
};

#endif /* BoundedBuffer_ */
