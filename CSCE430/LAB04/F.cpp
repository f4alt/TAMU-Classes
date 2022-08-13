#include <bits/stdc++.h>

using namespace std;

int main() {
  int num_tests, numbers;
  string temp;

  cin >> num_tests;

  for (int z=0; z < num_tests; z++) {
    priority_queue<string> pq;
    bool bad = false;
    cin >> numbers;

    for (int i=0; i < numbers; i++) {
      cin >> temp;

      pq.push(temp);
    }

    while (pq.size() > 1) {
      string cmp1 = pq.top();
      pq.pop();
      string cmp = cmp1.substr(0, pq.top().size());


      // cout << "cmp1:" << cmp1 << " | cmp:" << cmp << " | top:" << pq.top() << endl;
      if (cmp == pq.top()) {
        // cout << cmp << " | " << pq.top() << endl;
        bad = true;
        break;
      }
    }

    if (!bad) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }

  return 0;
}
