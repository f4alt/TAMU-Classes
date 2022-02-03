#include <bits/stdc++.h>

using namespace std;

int main() {
  int qnty;
  vector<long long> full, potentials_max, potentials_min;
  std::vector<long long>::iterator it;
  long long temp;
  int ans=0;
  long long max=-1, min=LLONG_MAX;

  cin >> qnty;

  for (int i=0; i < qnty; i++) {
    cin >> temp;

    // test max's
    if (max <= temp) {
      potentials_max.push_back(temp);
    }
    if (max < temp) {
      max = temp;
    }

    full.push_back(temp);
  }

  sort(potentials_max.begin(), potentials_max.end());

  for (int i=full.size()-1; i >= 0; i--) {
    if (min > full[i]) {
      potentials_min.push_back(full[i]);
      // too slow
      // it = find(potentials_max.begin(), potentials_max.end(), full[i]);
      // if (it != potentials_max.end()) {
      //   ans++;
      // }
      while (potentials_max.back() >= full[i] && potentials_max.size() > 0) {
        // cout << potentials_max.back() << " | " << full[i] << endl;
        if (potentials_max.back() == full[i]) {
          ans++;
          // cout << "HERE" << endl;
          break;
        }
        potentials_max.pop_back();
      }
      min = full[i];
    }
  }

  // potentials_max.pop_back();

  // for (int i=0; i < potentials_max.size(); i++) {
  //   cout << potentials_max[i] << endl;
  // }
  //
  // cout << endl;
  // for (int i=0; i < potentials_min.size(); i++) {
  //   cout << potentials_min[i] << endl;
  // }
  //
  // cout << endl;
  cout << ans << endl;


}
