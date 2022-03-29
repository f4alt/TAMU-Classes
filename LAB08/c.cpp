#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, queries, temp;
  int case_num =1;

  while (cin >> n) {
    vector<int> v(n);

    for (int i=0; i < n; i++) {
      cin >> v[i];
    }

    cin >> queries;

    cout << "Case " << case_num++ << ":" << endl;

    float l = 0;
    float r = n-1;
    // float mid = (l + r) / 2.0;
    while (queries--) {
      cin >> temp;

      while (true) {
        int minus = v[r] + v[l];
        int movel = l+1;
        int mover = r-1;

        if (abs(temp - minus) > abs(temp - (v[r] - v[movel]))) {
          l = movel;
        } else if (abs(temp - minus) < abs(temp - (v[mover] - v[l]))) {
          r = mover;
        } else if (movel == r || mover == l) {
          break;
        } else {
          break;
        }
      }

      cout << l << " | " << r << endl;
    }

  }










  return 0;
}
