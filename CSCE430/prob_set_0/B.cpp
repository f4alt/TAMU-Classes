#include <iostream>

using namespace std;

int main() {
  int quantity=0, total=0;

  cin >> quantity;

  int temp;
  for (int i=0; i<quantity; i++) {
    cin >> temp;
    total += temp;
  }

  cout << total;
}
