#include <bits/stdc++.h>

using namespace std;

int main() {
  // cube root 400000 = 73
  // cube root 200000 = 58.blah
  int possibilites[620000] = {0};
  map<pair<int, int>, int> pairs;

  int looking;
  cin >> looking;

  for (int i=1; i <= 74; i++) {
    for (int j=1; j <= 59; j++) {
      int idx = pow(i, 3) + pow(j, 3);

      // cout << idx << endl;
      if (pairs.count(make_pair(i, j)) > 0 ||
          pairs.count(make_pair(j, i)) > 0) {
        continue;
      }
      pairs[make_pair(i, j)] = 1;
      pairs[make_pair(j, i)] = 1;
      possibilites[idx]++;
    }
  }

  while (looking > 0) {
    if (possibilites[looking] >= 2) {
      // cout << possibilites[looking] << endl;
      cout << looking << endl;
      return 0;
    }
    looking--;
  }

  cout << "none\n";

  return 0;
}
