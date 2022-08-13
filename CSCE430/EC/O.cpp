#include <bits/stdc++.h>

using namespace std;

int amt_max;
int groups=0;

bool cust (int i, int j) {return (i > j); }

int dp(vector<int>& val, int amt) {
  if (amt == 0) {
    groups++;
    dp(val, amt_max);
    // return 1;
  }
  if (val.size() == 0) {
    return 1;
  }

  vector<int> temp = val;
  int take = amt - val.back();
  temp.pop_back();
  int top = dp(temp, take);
  int btm = dp(temp, amt);

  return min(top, btm);
  // return 0;
}

int main() {
  int numc;
  cin >> numc >> amt_max;

  vector<int> val;
  val.resize(numc);

  for (int i=0; i < numc; i++) {
    cin >> val[i];
  }

  sort(val.begin(), val.end(), cust);

  if (dp(val, amt_max) == 1) {
    cout << groups << endl;
  }
  // cout << dp(val, amt_max) << endl;

  return 0;
}
