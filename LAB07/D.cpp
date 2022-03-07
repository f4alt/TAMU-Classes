#include <bits/stdc++.h>

using namespace std;

int main() {
  int size, k, step=1;

  cin >> size >> k;

  for (int i=1; i < size; i++) {
    // cout << i << endl;
    if (i == size-1) {
      break;
    }

    if (i % k == 0) {
      // cout << "here" << endl;
      i += k;
    }

    step++;
  }

  cout << step << endl;

  return 0;
}
