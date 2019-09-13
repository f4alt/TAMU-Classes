#include "functions.h"

//checks how many instancs of digit are in n
int countDigitOccurrences(int n, int digit) {
  int checkdigit;
  int occurrances = 0;

  if (n < 0) {
    n = n * -1;
  }
  while (n > 0) {
    checkdigit = n % 10;
    if (checkdigit == digit) {
      occurrances++;
    }
    else {
      //do nothing
    }
    n = n / 10;
  }
  return occurrances;
}

//returns the last digit of n
int lastdigit(int n) {
  int digit;
  digit = n % 10;
  return digit;
}

 //returns n without the last digit
int peel(int n) {
  n = n / 10;
  return n;
}
