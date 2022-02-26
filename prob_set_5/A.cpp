#include <bits/stdc++.h>

using namespace std;

int main() {
  int queries, lower, higher, rooms, checkLow, checkHigh;
  vector<pair<int, int>> pref;

  scanf("%d\n", &queries);
  pref.resize(queries);
  rooms = 1;

  for (int i=0; i < queries; i++) {
    scanf("%d %d\n", &lower, &higher);
    pref[i] = make_pair(lower, higher);
  }

  sort(pref.begin(), pref.end());

  higher = pref[0].second;
  for (int i=1; i < pref.size(); i++) {
    if (pref[i].first <= higher) {
      if (pref[i].second < higher) {
        higher = pref[i].second;
      }
    } else {
      rooms++;
      higher = pref[i].second;
    }
  }

  cout << rooms << endl;


  return 0;
}
