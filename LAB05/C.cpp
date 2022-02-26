#include <bits/stdc++.h>

using namespace std;

int main() {
  int needed, to_reg, to_office, res=0;
  bool on_zero = true;

  cin >> needed >> to_reg >> to_office;
  // cout << "cal:" << ((needed - to_reg) / to_office) * to_office << endl;
  // cout << ((needed - to_reg) % to_office) * to_office*2 + to_reg*2 << endl;

  while (true) {
    if (on_zero && res+to_reg >= needed) {
      res += to_reg;
      break;
    } else if (!on_zero && res + (to_reg - to_office) >= needed) {
      res += to_reg - to_office;
      break;
    } else {
      res += to_office;
      on_zero = !on_zero;
    }
  }

  cout << res + to_reg << endl;



  return 0;
}
