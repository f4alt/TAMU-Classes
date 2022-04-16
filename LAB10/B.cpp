#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, temp, total=0;
  priority_queue<int> pq;

  cin >> n;

  while (n--) {
    cin >> temp;
    pq.push(temp);
  }

  while (pq.size() >= 3) {
    total += pq.top();
    pq.pop();
    total += pq.top();
    pq.pop();
    pq.pop();
  }

  while (!pq.empty()) {
    total += pq.top();
    pq.pop();
  }

  cout << total << endl;









  return 0;
}
