#include <iostream>
#include "functions.h"

using std::cout;
using std::cin;
using std::endl;

int main() {
  int startinterger = 0;
  int endinterger = 0;
  int checkdigit = 0;
  int numberlength = 1;
  int validnumbers = 0;

//inputs
  cout << "Enter numbers a <= b: ";
  cin >> startinterger;
  cin >> endinterger;

//break conditions
  if (startinterger <= 0 || endinterger > 10000 || endinterger < startinterger) {
    cout << "Invalid input" << endl;
    return 0;
// loop from start to end and check for repeated digits in the number 
  } else {
  for (int i = startinterger; i <= endinterger; i++) {
    numberlength = peel(i);
    checkdigit = lastdigit(i);
    if (numberlength == 0) {
      validnumbers++;
    } else {
    while (numberlength >= 0) {
    if (numberlength == 0) {
      validnumbers++;
      break;
    } else if (countDigitOccurrences(numberlength, checkdigit) == 0) {
        checkdigit = lastdigit(numberlength);
        numberlength = peel(numberlength);
      } else if (countDigitOccurrences(numberlength, checkdigit) > 0) {
        break;
      }
    }
  }
}
  cout << "There are " << validnumbers << " valid numbers between " << startinterger << " and " << endinterger << endl;
}
  return 0;
}
