#include <bits/stdc++.h>

using namespace std;

vector<long long> val;

long long count(int m, int n)
{
 int table[n+1];
 // Initialize all table values as 0
 memset(table, 0, sizeof(table));
 // Base case (If given value is 0)
 table[0] = 1;

 for(int i=0; i<m; i++) {
   for(int j=val[i]; j<=n; j++) {
     table[j] += table[j-val[i]];
   }
 }
 return table[n];
}

pair<int, string> dp(int a, int b) {
  if (a == 0) {
    return make_pair(0, "");
  }
  if (b < 0) {
    return make_pair(INT_MAX-1, "inf");
  }
  if (a < 0) {
    return make_pair(INT_MAX-1, "inf");
  }
  static map<pair<int, int>, pair<int, string>> mydp;

  if (mydp.count(make_pair(a, b)) > 0) {
    return mydp[make_pair(a, b)];
  }
  pair<int, string> retval;
  pair<int, string> top = dp(a-val[b],b);
  pair<int, string> bottom = dp(a, b-1);

  if (top.first + 1 < bottom.first) {
    retval = top;
    retval.first++;
    retval.second.append(to_string(b+1) + " ");
  } else {
    retval = bottom;
  }

  mydp[make_pair(a, b)] = retval;
  return retval;
}

int main() {
  int numc;
  cin >> numc;

  val.resize(numc);

  for (int i=0; i < numc; i++) {
    cin >> val[i];
  }

  int queries;
  cin >> queries;
  while (queries--) {
    int amt;
    cin >> amt;
    long long ways = count(numc, amt);
    if (ways == 0) {
      cout << "Impossible\n";
    } else if (ways > 1) {
      cout << "Ambiguous\n";
    } else {
      cout << dp(amt, numc-1).second << "\n";
    }
  }

  return 0;
}
