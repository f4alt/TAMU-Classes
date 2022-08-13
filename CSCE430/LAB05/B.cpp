#include <bits/stdc++.h>

using namespace std;

int main() {
  int row, col, maxR=0, maxC=0, temp;

  cin >> row >> col;

  while (row--) {
    cin >> temp;
    maxR = max(maxR, temp);
  }

  while (col--) {
    cin >> temp;
    maxC = max(maxC, temp);
  }

  if (maxR == maxC) {
    cout << "possible" << endl;
  } else {
    cout << "impossible" << endl;
  }

  return 0;
}
