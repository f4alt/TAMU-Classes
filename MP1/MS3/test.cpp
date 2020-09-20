#include <iostream>

using namespace std;

int main() {
  int block_size = 100;
  int size = 100;
  int allocated = 0;

  allocated = ((block_size + size - 1) / block_size) * block_size;

  cout << allocated << endl;
}
