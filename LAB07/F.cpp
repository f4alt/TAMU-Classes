#include <bits/stdc++.h>

using namespace std;

vector<long long> val;

// void dp(int a, int b) {
//   if (a == val.size()) {
//     return;
//   }
//   if (b == 0) {
//     return;
//   }
//   static map<pair<int, int>, int> > mydp;
//
//   if (mydp.count(make_pair(a, b)) > 0) {
//     return;
//   }
// }

int main() {
  int room, sizes;
  cin >> room >> sizes;
  set<int> options;

  val.resize(sizes+2);

  for (int i=0; i < sizes; i++) {
    cin >> val[i];
  }
  val[sizes]=room;
  val[sizes+1]=0;

  // cout << val.size() << endl;

  // vector<int> ans(room+1, -1);

  // dp(0, sizes+1);
  for (int i=0; i < val.size(); i++) {
    for (int j=i+1; j < val.size(); j++) {
      // cout << i << " | " << j << endl;
      // cout << abs(val[j] - val[i]) << endl;
      int insert = abs(val[j] - val[i]);
      options.insert(insert);
    }
  }

  for (auto i : options) {
    if (i == 0) {
      continue;
    }
    cout << i << " ";
  }
  cout << endl;
  // while (!options.empty()) {
  //   cout << -options.top() << " ";
  //   options.pop();
  // }

  return 0;
}
