#include <bits/stdc++.h>

using namespace std;

vector<int> vals;
bool mydp[1000001];

// bool dp(int left) {
//   return true;
// }

int main() {
  int num_stones, num_vals;

  cin >> num_stones >> num_vals;
  while (!cin.eof()) {

    vals.resize(num_vals);
    memset(mydp, false, sizeof(mydp));

    for (int i=0; i < num_vals; i++) {
      cin >> vals[i];
    }

    for (int i=1; i <= num_stones; i++) {
      for (int j=0; j < vals.size(); j++) {
        if (i >= vals[j] && !mydp[i-vals[j]]) {
          // cout << "i:" << i << " val:" << vals[j] << " | ";
          // cout << mydp[i-vals[j]] << endl;
          mydp[i] = true;
          break;
        }
      }
    }

    // if (dp(num_stones)) {
    if (mydp[num_stones]) {
      cout << "Stan wins\n";
    } else {
      cout << "Ollie wins\n";
    }
    cin >> num_stones >> num_vals;
  }

  return 0;
}
