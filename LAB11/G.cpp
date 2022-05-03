#include <bits/stdc++.h>

using namespace std;

int main() {
  long long N, temp, ans=0;
  long long worlds[500000];

  cin >> N;

  for (int i=0; i < N; i++) {
    cin >> worlds[i];
  }

  if (worlds[N-1] < N-1) {
    cout << "1" << endl;
    return 0;
  }

  for (int i=N-1; i > 0; i--) {
    if (worlds[i] <= worlds[i-1]) {
      // cout << worlds[i] << " | " << worlds[i-1] << endl;
      temp = worlds[i-1] + 1 - worlds[i];
      if (temp >= 0) {
        ans += temp;
        worlds[i-1] = worlds[i] - 1;
      } else {
        cout << "1" << endl;
        return 0;
      }

      if (worlds[i-1] < 0) {
        cout << "1" << endl;
        return 0;
      }
    }
  }


  cout << ans << endl;



  return 0;
}
