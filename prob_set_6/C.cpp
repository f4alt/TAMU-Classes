#include <bits/stdc++.h>

using namespace std;

int main() {
  int rooms, close, left, right;

  cin >> rooms >> close;
  while (rooms != 0 && close != 0) {
    for (int i=0; i < rooms; i++) {
      cin >> left >> right;
    }

    cout << "end gallery" << endl;
    cin >> rooms >> close;
  }

  return 0;
}
