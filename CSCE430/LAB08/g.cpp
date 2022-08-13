#include <bits/stdc++.h>

using namespace std;

vector<int> vals;
vector<int> prefix;
int n;
int cost;
int stop = 0;

int dp(int curr_pos) {
  if (curr_pos == -1) {
    return 0;
  }
  if (curr_pos < 0) {
    return -1000000;
  }

  static map<int, int> mydp;

  if (mydp.count(curr_pos) > 0) {
    return mydp[curr_pos];
  }

  int curr = vals[curr_pos] - cost;

  int skip = dp(curr_pos -1);
  int keep_going = curr + dp(curr_pos-1);
  int ret = max(skip, keep_going);

  // int decide = max(stop, ret);

  // mydp[curr_pos] = decide;
  return ret;
}

int main() {
  int temp;

  cin >> n >> cost;

  prefix.resize(n+1, 0);

  // cin >> prefix[0];
  // prefix[0] -= cost;
  for (int i=0; i < n; i++) {
    // cin >> temp;
    // cin >> vals[i];
    // prefix[i] += prefix[i-1] + temp -cost;
    cin >> prefix[i];
    prefix[i] -= cost;
  }

  // for (int i=0; i < n; i++) {
  //   cout << prefix[i] << " " ;
  // }
  // cout << endl;

  int ans = 0;
  temp =0;
  // for (int i=n-1; i >= 0; i--) {
    for (int j=0; j < n; j++) {
      temp = max(temp + prefix[j], 0);
      ans = max(ans, temp);
    }
  // }

  cout << ans << endl;

  // cout << dp(n-1) << endl;
  // cout << stop << endl;










  return 0;
}
