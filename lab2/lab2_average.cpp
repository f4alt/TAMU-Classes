#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
  int input, input_amount = 0, running_total = 0;
  float average;
  cin >> input;
  do
  {
    running_total += input;
    cin >> input;
    ++input_amount;
  }
  while (input != 0);
  average = running_total / input_amount;
  cout << "avg: " << fixed << setprecision(4) << average << endl;
  return 0;
}
