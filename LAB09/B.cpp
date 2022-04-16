#include <bits/stdc++.h>

using namespace std;

int main() {int cases;
  cin >> cases;

  while(cases--) {
    int l, n;
    cin >> l >> n;

    vector<int> v(n);

    for (int i=0; i < n; i++) {
      cin >> v[i];
    }

    int low = min(v[0], l-v[0]);
    int high = max(v[0], l-v[0]);

    for (int i=0; i < n; i++) {
      low = max(low, min(v[i], l-v[i]));
      high = max(high, max(v[i], l-v[i]));
    }

    cout << low << " " << high << endl;
  }










    return 0;
}
