#include <iostream>

using namespace std;

//returns false if negative or has a divisor
bool prime_check(int n)
{
  if (n <= 1)
  {
    return false;
  }
//check all numbers to see if there are any divisors
  for(int i = 2; i < n; ++i)
    if(n % i == 0)
      return false;

  return true;
}

int main()
{
  int input;
  int counter = 0;
  do
  {
    cin >> input;
    if (prime_check(input) == true)
    {
      ++counter;
    }
  }
  while (input != 0);
  cout << counter << endl;
  return 0;
}
