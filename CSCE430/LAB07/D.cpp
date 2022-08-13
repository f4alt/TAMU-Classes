#include <bits/stdc++.h>

using namespace std;

int main() {
  long long n, k, step=1;

  cin >> n >> k;

  // for (int i=1; i < size; i++) {
  //   // cout << i << endl;
  //   if (i == size-1) {
  //     break;
  //   }
  //
  //   if (i % k == 0) {
  //     // cout << "here" << endl;
  //     i += k;
  //   }
  //
  //   step++;
  // }
  //
  if (n-1 < 2*k) {
    cout << n-1 << endl;
  } else {
    cout << k+1+(n-1)%k << endl;
  }

  // cout << step << endl;

  return 0;
}
