#include <bits/stdc++.h>

using namespace std;

int main() {
  queue<int> requests;
  int upcoming, max, curr;
  int needed=0;

  cin >> upcoming >> max;

  for (int i=0; i < upcoming; i++) {
    cin >> curr;
    if (curr > 1000) {
      // needed++;
      // cout << "adding 1 to queue" << endl;
      if (requests.front() < 1000) {
        requests.pop();

        // cout << "front is done" << endl;
      } else {
        // cout << "updating front, inc needed" << endl;
        requests.front() -= 1000;
        needed++;
      }
      requests.push(curr);
    }
  }

  float ans = ceil((float)needed / (float)max);
  cout << ans << endl;
}
