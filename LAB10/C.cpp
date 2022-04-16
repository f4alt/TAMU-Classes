#include <bits/stdc++.h>

using namespace std;

bool cust(const pair<int,int> &a, const pair<int,int> &b) {
  if (a.second == b.second) {
    return a.first < b.first;
  } else {
    return a.second > b.second;
  }
    // return (a.second < b.second);
}


int main() {
  int N, T, ni, ti, served1=0, served2=0;
  long long ans1=0, ans2=0;
  vector<pair<int, int> > pq_val, pq_amt;

  cin >> N >> T;

  while (N--) {
    cin >> ni >> ti;

    pq_val.push_back(make_pair(ti, ni));
    // pq_amt.push(make_pair(ni, -ti));
  }

  sort(pq_val.begin(), pq_val.end(), cust);


  for (int i=0; i < pq_val.size(); i++) {
    ans1 += pq_val[i].first;
    served1++;
    if (served1 > T) {
      break;
    }
  }

  cout << ans1 << endl;
  // while (!pq_val.empty()) {
  //   pair<int, int> val = pq_val.top();
  //   pair<int, int> amt = pq_amt.top();
  //   pq_val.pop();
  //   pq_amt.pop();
  //
  //   // cout << val.first << " | " << val.second << endl;
  //   // cout << amt.first << " | " << amt.second << endl;
  //
  //   if (-val.first >= served1 && served1 <= T) {
  //     ans1 += val.second;
  //     served1++;
  //   }
  //
  //   if (-amt.second >= served2 && served2 <= T) {
  //     ans2 += amt.first;
  //     served2++;
  //   }
  // }

  // sorted.resize(pq.size());
  // for (int i=0; i < sorted.size(); i++) {
  //   sorted[i] = pq.top();
  //   pq.pop();
  // }
  //
  // for (int i=0; i < sorted.size(); i++) {
  //   pair<int, int> curr = sorted[i];
  //   // cout << curr.first << " | " << curr.second << endl;
  //   if (-curr.first >= served && served < T) {
  //     ans += curr.second;
  //     served++;
  //   }
  // }



  cout << max(ans1, ans2) << endl;












  return 0;
}
