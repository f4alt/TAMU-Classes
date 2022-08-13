#include <bits/stdc++.h>

using namespace std;

int main() {
  int needed, to_reg, to_office, total=0;

  cin >> needed >> to_reg >> to_office;

  total += to_office;
  total += abs(to_office - to_reg);

  while (total < needed) {
    total += 2;
  }

  total += to_reg;

  cout << total << endl;



  return 0;
}
