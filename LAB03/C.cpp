#include <bits/stdc++.h>

using namespace std;

int main() {
  long long a, b, a_orig, b_orig;
  std::unordered_map<long long, long long>::iterator it;
  std::unordered_map<long long, long long>::iterator it2;

  while (true) {
    // reset seta
    unordered_map<long long, long long> seta;

    // take in numbers
    cin >> a >> b;
    if (a == 0 && b == 0) { // break condition
      break;
    }

    // keep track of originals
    a_orig = a;
    b_orig = b;
    int i=0;

    // loop all the way through a until it hits 1
    for (i; ;i++) {
      // insert val in unordered map
      seta.insert(std::pair<int, int>(a, i) );

      if (a == 1) { // break condition
        break;
      }

      // calcualte next a
      if (a % 2 == 0) {
        a = a/2;
      } else {
        a = 3*a + 1;
      }
    }

    // solve through B and break when we find it in a
    for (i=0;;i++) {
      // search for b in a
      it = seta.find(b);
      if (it != seta.end()) { // break condition
        break;
      }
      // calcualte next b
      if (b % 2 == 0) {
        b = b/2;
      } else {
        b = 3*b + 1;
      }
    }

    cout << a_orig << " needs " << it->second << " steps, " << b_orig << " needs " << i << " steps, they meet at " << it->first << endl;
  }




  return 0;
}
