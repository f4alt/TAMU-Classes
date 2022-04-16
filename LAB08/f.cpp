#include <bits/stdc++.h>

using namespace std;

int main() {
  int N, K, len, letters, rem=0, ans=0;
  priority_queue<pair<int, int> > pos, neg;

  cin >> N >> K;

  for (int i=0; i < N; i++) {
    cin >> len >> letters;

    if (len >= 0) {
      pos.push({len, letters});
    } else {
      neg.push({-len, letters});
    }
  }

  while (!pos.empty()) {
    pair<int, int> temp = pos.top();
    pos.pop();

    // check if we have enough remaining to avoid extra trips
    if (rem < temp.second) {
      // cout << "adding:" << temp.first << " | " << temp.second << endl;
      ans += temp.first * 2;
      rem += K;
    }

    rem -= temp.second;

    if (rem < 0) {
      pos.push({temp.first, -rem});
      rem = 0;
    }
    // cout << "rem:" << rem << endl;
  }

  rem = 0;
  while (!neg.empty()) {
    pair<int, int> temp = neg.top();
    neg.pop();

    // check if we have enough remaining to avoid extra trips
    if (rem < temp.second) {
      // cout << "adding:" << temp.first << " | " << temp.second << endl;
      ans += temp.first * 2;
      rem += K;
    }

    rem -= temp.second;

    if (rem < 0) {
      neg.push({temp.first, -rem});
      rem = 0;
    }
  }

  cout << ans << endl;

















  return 0;
}
