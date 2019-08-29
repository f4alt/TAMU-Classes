#include <iostream>

using namespace std;

int main(){
  cout << "Input a list of numbers ended with 0" << endl;
  int n;
  int sum = 0;
  while (n != 0){
    cin >> n;
    sum += n;
  }

  cout << "Your numbers add up to " << sum << endl;

  return 0;
}
