#include <bits/stdc++.h>

using namespace std;

int main() {
  int first, second, res;

  cin >> first >> second;
  res = second - first;

  if (res == 1 || res == 0) {
    cout << "Dr. Chaz will have " << res << " piece of chicken left over!\n";
  } else if (res > 1) {
    cout << "Dr. Chaz will have " << res << " pieces of chicken left over!\n";
  } else if (res == -1) {
    cout << "Dr. Chaz needs " << -res << " more piece of chicken!\n";
  } else {
    cout << "Dr. Chaz needs " << -res << " more pieces of chicken!\n";
  }



  return 0;
}
