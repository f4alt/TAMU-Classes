#include <iostream>

using namespace std;

int inputted_amount = 1;

bool check_decending(int input)
{
  int first_input = input, next_input;

  do
  {
    if (next_input < first_input)
    {
      cout << "returned true" << endl; //test line
      return true;
    }
    else
    {
      return false;
      break;
    }
    first_input = next_input;
    cin >> next_input;
  }
  while (next_input != 0);
}

int main()
{
  check_decending();
  if (check_decending() == true)
  {
    cout << inputted_amount << " sorted" << endl;
  }
  return 0;
}
