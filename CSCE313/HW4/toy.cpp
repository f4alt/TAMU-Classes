#include <iostream>
using namespace std;

int main (int argc, char * argv[]) {
  for(;;) {
    int val;
    cin >> val;
    if (val == 0)
      break;
    else if (val % 2 == 0)
      cout << "value " << val << " is even!";
    else
      cerr << "value " << val << " is odd!";
  }
}
