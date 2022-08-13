#include <bits/stdc++.h>

using namespace std;

int main() {
  int N, H, temp;
  // int stalag, stalac;
  vector<int> stalag, stalac;

  cin >> N >> H;

  for (int i=0; i < N; i++) {
    cin >> temp;
    if (i % 2 == 0) {
      stalag.push_back(temp);
    } else {
      stalac.push_back(temp);
    }
  }

  sort(stalag.begin(), stalag.end());
  sort(stalac.begin(), stalac.end());

  if (stalag.back() + stalac.back() < H) {
    cout << "0 " << H/2 << endl;
  } else {

  }










  return 0;
}
