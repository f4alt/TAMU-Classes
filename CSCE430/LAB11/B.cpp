#include <bits/stdc++.h>

using namespace std;

int main() {
  long long D;
  double needed;

  cin >> D;

  long long squares[200000];

  for (long long i=0; i < 200000; i++) {
    squares[i] = i * i;
  }

  for (int i=sqrt(D); i < 200000; i++) {
    needed = squares[i] - D;

    if ((sqrt(needed) - floor(sqrt(needed))) == 0) {
      cout << min(i, (int)sqrt(needed)) << " " << max(i, (int)sqrt(needed)) << endl;
      return 0;
    }
  }

  cout << "impossible" << endl;










  return 0;
}
