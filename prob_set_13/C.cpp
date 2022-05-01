#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;

  while(cin >> n && n != 4) {
    int times = 0;
    while(true) {
      times++;

      vector<int> factors;
      for (int i = 2; i <= sqrt(n); i++) {
        while(n % i == 0) {
          n /= i;
          factors.push_back(i);
        }
      }
      if (n > 1) {
        factors.push_back(n);
      }


      if (factors.size() == 1) {
        cout << factors[0] << " " << times << endl;
        break;
      }

      int total = 0;
      for(int i=0; i < factors.size(); i++) {
        total += factors[i];
      }
      n = total;
    }
  }






  return 0;
}
