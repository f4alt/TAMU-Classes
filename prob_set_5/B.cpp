#include <bits/stdc++.h>

using namespace std;

int main() {
  long long base;

  while (scanf("1/%lld\n", &base) != EOF) {
    int total=0;

    for (long long i=1; i <= base*base; i++) {
      if (base*base % i == 0) {
        total++;
        if (i == base) {
          break;
        }
      }
    }

    cout << total << endl;
  }




  return 0;
}
