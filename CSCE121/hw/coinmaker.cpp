#include <iostream>
using namespace std;

//global variables
int dollars, cents, quarters, dimes, nickels, pennies, total_change;

//input function converts dollars and cents all to cents
void input()
{
  cout << "Enter dollars: ";
  cin >> dollars;
  cout << "Enter cents: ";
  cin >> cents;
  total_change = (100 * dollars) + cents;
}

//check how many quarters are needed by dividing total by 25 and updating total
int quarters_needed()
{
  quarters = total_change / 25;
  total_change = total_change - (25 * quarters);
  return quarters;
}
//check how many dimes are needed by dividing total by 10 and updating total
int dimes_needed()
{
  dimes = total_change / 10;
  total_change = total_change - (10 * dimes);
  return dimes;
}
//check how many nickels are needed by dividing total by 5 and updating total
int nickels_needed()
{
  nickels = total_change / 5;
  total_change = total_change - (5 * nickels);
  return nickels;
}

int main()
{
  input();
  quarters_needed();
  dimes_needed();
  nickels_needed();

  cout << "Pennies: " << total_change << endl; //remaining change in total is pennies
  cout << "Nickels: " << nickels << endl;
  cout << "Dimes: " << dimes << endl;
  cout << "Quarters: " << quarters << endl;
  cout << "\n";
  cout << "Total coins used: " << quarters + nickels + dimes + total_change << endl;
}
