//Given a 0-terminated newline-delimited sequence of integers from standard input (i.e. cin), print the minimum value to standard output
//(i.e. cout). If the list is empty, print "empty"

#include <iostream>

using namespace std;

int main(){
// welcome statement and define variables
  int n;
  int min_value;
  cin >> n;
  min_value = n;
  if (min_value == 0){
    cout << "empty" << endl;
  }
  else {
// if input is lesser than last, replace as lowest
  while (n != 0){
    if (n > min_value){
      min_value = n;
    }
    cin >> n;
  }
// output results
  cout << "max: " << min_value << endl;
}
}
