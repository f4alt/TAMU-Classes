#include <bits/stdc++.h>

using namespace std;

int main() {
  long long n, H=0, seen=0, temp;
  priority_queue<long long> forward, reverse;

  cin >> n;

  while (n--) {
    cin >> temp;
    forward.push(temp);
    reverse.push(-temp);
  }

  while (!reverse.empty()) {
    long long possibleH = -reverse.top();
    long long forH = forward.top();
    seen++;

    // long long possibleH = forward.top();

    // cout << possibleH << " | " << reverse.size() << endl;

    if (possibleH <= reverse.size()) {
      H = possibleH;
    }
    if (forH > H) {
      H = max(seen, H);
    }


    reverse.pop();
    forward.pop();

  }

  cout << H << endl;

















  return 0;
}
