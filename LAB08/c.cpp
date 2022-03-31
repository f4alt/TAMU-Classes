#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, queries, temp;
  int case_num =1;

  while (cin >> n) {
    cout << "Case " << case_num++ << ":" << endl;

    vector<int> v(n);

    for (int i=0; i < n; i++) {
      cin >> v[i];
    }

    cin >> queries;


    float l = 0;
    float r = n-1;
    int ans;
    // float mid = (l + r) / 2.0;
    while (queries--) {
      cin >> temp;
      ans = v[0] + v[1];

      for(int i = 0; i < n; i++) {
            for( int j = i+1; j < n; j++) {
                int cur = v[i] + v[j];
                if(abs(ans - temp) > abs(cur - temp)) {
                  ans = cur;
                }
            }
        }
        cout << "Closest sum to " << temp << " is " << ans << "." << endl;
      }

      // while (true) {
      //   int minus = v[r] + v[l];
      //   int movel = l+1;
      //   int mover = r-1;
      //
      //   if (abs(temp - minus) > abs(temp - (v[r] - v[movel]))) {
      //     l = movel;
      //   } else if (abs(temp - minus) < abs(temp - (v[mover] - v[l]))) {
      //     r = mover;
      //   } else if (movel == r || mover == l) {
      //     break;
      //   } else {
      //     break;
      //   }
      // }
      //
      // cout << l << " | " << r << endl;
    // }

  }










  return 0;
}
