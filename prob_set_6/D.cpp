#include <bits/stdc++.h>

using namespace std;

vector<int> cost;

int dp(int curr, int last_move) {
  cout << curr << " | " << last_move << endl;
  if (curr == cost.size()-1) {
    // return cost[cost.size()-1];
    return 0;
  }
  if (curr >= cost.size()) {
    // return cost.size();
    return INT_MAX;
  }
  if (curr < 0) {
    // return cost.size();
    return INT_MAX;
  }
  // static map<pair<int, int>, int> mydp;
  //
  // if (mydp.count(make_pair(curr, last_move)) > 0) {
  //   return mydp[make_pair(curr, last_move)];
  // }
  int retval;
  retval = min(dp(curr+last_move+1, last_move+1) + cost[curr+last_move+1],
               dp(curr-last_move, last_move) + cost[curr-last_move]);
  cout << "cost:" << retval << endl;
  // mydp[make_pair(curr, last_move)] = retval;
  return retval;
}

int main() {
  int squares;

  cin >> squares;

  cost.resize(squares+1);

  for (int i=0; i < squares; i++) {
    cin >> cost[i];
  }
  cost[squares] = INT_MAX;

  cout << dp(1, 1) << "\n";

  return 0;
}
