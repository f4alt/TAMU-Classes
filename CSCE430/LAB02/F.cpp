#include <bits/stdc++.h>

using namespace std;

int main() {
  double qnty, ncs_qnty, ne_qnty, ncs_avg, ne_avg, temp, ans=0;
  vector<double> ncs, ne, potential;

  cin >> qnty;

  for (int i=0; i < qnty; i++) {
    // cin >> temp;
    cin >> ncs_qnty >> ne_qnty;

    for (int j=0; j < ncs_qnty; j++) {
      cin >> temp;

      ncs.push_back(temp);
    }

    for (int j=0; j < ne_qnty; j++) {
      cin >> temp;

      ne.push_back(temp);
    }

    ncs_avg = accumulate(ncs.begin(), ncs.end(), 0) / ncs_qnty;
    ne_avg = accumulate(ne.begin(), ne.end(), 0) / ne_qnty;

    // cout << ncs_avg << " | " << ne_avg << endl;

    for (int j=0; j < ncs_qnty; j++) {
      if (ncs[j] < ncs_avg && ncs[j] > ne_avg || ncs[j] < ncs_avg && ne_qnty == 0) {
        // potential.push_back(ncs[j]);
        ans ++;
      }
    }

    cout << ans << endl;
    ans=0;
    ncs.clear();
    ne.clear();
  }



  return 0;
}
