#include <bits/stdc++.h>

using namespace std;

struct device {
  long long x, y, r;
};

int main() {
  long long cx, cy, n;

  long long devInRange = 0;
  long long calcRad = -1;
  long long ans = 0;


  cin >> cx >> cy >> n;

  vector<device> devices(n);

  // intake
  for (int i = 0; i < n; i++) {
    cin >> devices[i].x >> devices[i].y >> devices[i].r;
  }

  while (devInRange < 3) {
    calcRad++;
    devInRange = 0;

    for (int i = 0; i < n; i++) {
      if (sqrt((long double)(devices[i].x - cx) * (devices[i].x - cx) +
      (devices[i].y - cy) * (devices[i].y - cy)) <
      devices[i].r + calcRad) {
        devInRange++;
      }
    }
    if (devInRange < 3) {
      ans = calcRad;
    }
  }

  cout << ans << endl;













  return 0;
}
