//even counter

#include <iostream>

using namespace std;

int main(){
  int n;
  int counter = 0;
  int check;
  do {
    if (check == 0) {
      counter += 1;
    }
    cin >> n;
    check = n % 2;
  }
  while (n != 0);
  cout << counter << endl;
}
