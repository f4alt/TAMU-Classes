#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
  float input, input_amount = 0, running_total = 0, average;
  cin >> input;
  if (input == 0)
  {
    cout << "empty" << endl;
  }
  else
  {
  do
  {
    running_total += input;
    cin >> input;
    ++input_amount;
  }
  while (input != 0);

  average = running_total / input_amount;
  cout << "avg: " << average << endl;
  }
  return 0;
}
