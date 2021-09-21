#include "BuddyAllocator.h"
#include <iostream>
#include <math.h>
using namespace std;

BlockHeader* BuddyAllocator::split (BlockHeader* b) {
	int bs = b->block_size;
	b->block_size /= 2;
	b->next = nullptr;

	// advance block pointer to second half
	BlockHeader* sh = (BlockHeader*)((char*)b + b->block_size);
	// sh->next = nullptr, sh->block_size = b->block_size
	BlockHeader* temp = new (sh) BlockHeader (b->block_size);
	return sh;
}

BuddyAllocator::BuddyAllocator (int _basic_block_size, int _total_memory_length){
	total_memory_size = _total_memory_length, basic_block_size = _basic_block_size;
	start = new char [total_memory_size];
	int l = log2(total_memory_size/basic_block_size);
	for (int i=0; i < l; i++) {
		FreeList.push_back(LinkedList());
	}
	FreeList.push_back(LinkedList((BlockHeader*)start));
	BlockHeader* h = new (start) BlockHeader (total_memory_size);
}

BuddyAllocator::~BuddyAllocator (){
	delete[] start;
}

char* BuddyAllocator::alloc(int _length) {
  /* This preliminary implementation simply hands the call over the
     the C standard library!
     Of course this needs to be replaced by your implementation.
  */
  // return new char [_length];

	// min size needed for requested length
	int x = _length + sizeof(BlockHeader);
	int idx = ceil(log2(ceil((double)x / basic_block_size)));
	int bsReturn = (1 << idx) * basic_block_size;

	// this->printlist();

	if (FreeList[idx].head != nullptr) {									// found correct block
		// cout << "breaking here?" << endl;
		BlockHeader* b = FreeList[idx].remove();
		// cout << "returning here?" << endl;
		b->is_free = 0;
		return (char*)(b+1);																// advance by size of bh and return
	}

	int idxCorrect = idx;				// backup to compare against
	for (; idx < FreeList.size(); idx++) {
		if (FreeList[idx].head) {					// index we are looking for
			// this->printlist();
			// cout << "idx:" << idx << endl;
			break;
		}
	}

	// cout << "req:" << _length << endl;
	// cout << "idx:" << idx << endl;
	// cout << "FL size:" << FreeList[0].list_size << endl;
	// cout << "math: " << basic_block_size * pow(2, idx) << endl;
	// cout << "bsREt:" << bsReturn << endl;

	if (idx >= FreeList.size()) {				// allocation could not happen
		// cout << "returning" << endl;
		return nullptr;
	}

	// bigger block found at idx
	while (idx > idxCorrect) {
		BlockHeader* b = FreeList[idx].remove();
		BlockHeader* secondHalf = split (b);
		--idx;
		FreeList[idx].insert(b);
		FreeList[idx].insert(secondHalf);
	}
	BlockHeader* block = FreeList[idx].remove();
	block -> is_free = 0;
	return (char*) (block +1);
}

BlockHeader* BuddyAllocator::getbuddy(BlockHeader* _b) {
	// return (BlockHeader*)((char*)((int)((char*)b - start) ^ b->block_size) + start);
	char* buddy;
	buddy = (char*)((((char*)_b- start) ^ _b->block_size) + start);
	return (BlockHeader*) buddy;
	}

BlockHeader* BuddyAllocator::merge (BlockHeader* sa, BlockHeader* ba) {
	BlockHeader* smaller;
	BlockHeader* larger;
	if (sa > ba) {
		// swap (sa, ba);
		smaller = ba;
		larger = sa;
	} else {
		smaller = sa;
		larger = ba;
	}

	smaller->block_size *= 2;
	return smaller;
}

int BuddyAllocator::free(char* _a) {
  /* Same here! */
  // delete _a;

	BlockHeader* b = (BlockHeader*)(_a - sizeof(BlockHeader));

	// recursive
	while (true) {
		int size = b->block_size;
		b->is_free = 1;
		int idx = getIndex(size);
		// cout << "req:" << size << endl;
		// cout << "idx:" << idx << endl;
		// cout << "FL size:" << FreeList.size() << endl;
		// this->printlist();
		if (idx == FreeList.size()-1) {
			FreeList[idx].insert(b);
			break;
		}
		BlockHeader* buddy = getbuddy(b);
		if (buddy->is_free && (b->block_size == buddy->block_size)) {
			b = merge(b, buddy);
			FreeList[idx].remove(buddy);
		} else {
			FreeList[idx].insert(b);
			break;
		}
	}

  return 0;
}

void BuddyAllocator::printlist (){
  cout << "Printing the Freelist in the format \"[index] (block size) : # of blocks\"" << endl;
  for (int i=0; i<FreeList.size(); i++){
    cout << "[" << i <<"] (" << ((1<<i) * basic_block_size) << ") : ";  // block size at index should always be 2^i * bbs
    int count = 0;
    BlockHeader* b = FreeList [i].head;
    // go through the list from head to tail and count
    while (b){
      count ++;
      // block size at index should always be 2^i * bbs
      // checking to make sure that the block is not out of place
      if (b->block_size != (1<<i) * basic_block_size){
        cerr << "ERROR:: Block is in a wrong list" << endl;
        exit (-1);
      }
      b = b->next;
    }
    cout << count << endl;
  }
}
