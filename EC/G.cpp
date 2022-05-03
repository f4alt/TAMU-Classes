#include <bits/stdc++.h>

using namespace std;

int main() {
  string in;

  cin >> in;

  if (in.size() <= 3) {
    cout << "NO" << endl;
    return 0;
  }
  if (in[0] != 'r') {
    cout << "NO" << endl;
    return 0;
  }
  if (in[in.size()-1] != 'r' || in[in.size()-2] != 'a') {
    cout << "NO" << endl;
    return 0;
  }

  for (int i=1; i <= in.size()-3; i++) {
    if (in[i] != 'o') {
      cout << "NO" << endl;
      return 0;
    }
  }

  cout << "YES" << endl;


  return 0;
}
