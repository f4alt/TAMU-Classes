#include <iostream>

using namespace std;

int main() {
  int* test_pointer;

  int test_array[] = {1,2,3};

  test_pointer = test_array;


  // test_pointer[2] = {1,2,3};

  cout << test_pointer[2] << endl;
}
