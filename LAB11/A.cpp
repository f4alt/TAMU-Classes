#include <bits/stdc++.h>

using namespace std;

int main() {
  long long S, capacity, color_dif, curr=0;

  vector<long long> socks(1000000, 0);
  // vector<pair<int, int> > groups(1000000, make_pair(0, 0));
  vector<list<int> > groups(100000);

  cin >> S >> capacity >> color_dif;

  for (int i=0; i < S; i++) {
    cin >> socks[i];
  }

  sort(socks.begin(), socks.begin()+S);

  // groups[0] = make_pair(socks[0], 1);
  groups[0].push_back(socks[0]);

  for (int i=1; i < S; i++) {
    if (socks[i] - groups[curr].front() <= color_dif) {
      // groups[curr].second += 1;
      groups[curr].push_back(socks[i]);
    }
    else {
      // cout << "bad difference:" << socks[i] << " | " << groups[curr].first << endl;
      curr += 1;
      // cout << "incr curr" << endl;
      // groups[curr] = make_pair(socks[i], 1);
      groups[curr].push_back(socks[i]);
    }

    if (groups[curr].size() > capacity) {
      curr += 1;
      // cout << "inc curr" << endl;
      groups[curr].push_back(groups[curr-1].back());
      // groups[curr].first = groups[curr-1].first;
      // groups[curr].second = 1;
    }

  }

  cout << curr+1 << endl;







  return 0;
}
