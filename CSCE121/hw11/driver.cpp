#include <iostream>
#include "Node.h"
#include "DoublyLinkedList.h"

using namespace std;

int main()
{
  DoublyLinkedList<int> list;
  // DoublyLinkedList<int> list2 = list;
  // list2.pop_back();
  DoublyLinkedList<int> list2;
  list2 = list;

  cout << list << endl;
  cout << list2 << endl;
  // cout << list3 << endl;
    return 0;
}
