#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;

  while (cin >> n && n != 0) {
    vector<vector<int>> grid(500, vector<int>(500, false));

    for (int i=0; i < n; i++) {
      int x1, x2, y1, y2;
      cin >> x1 >> y1 >> x2 >> y2;

      if (x1 > x2) {
        int temp;
        temp = x1;
        x1 = x2;
        x2 = temp;
      }

      if (y1 > y2) {
        int temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
      }

      for (int i=x1; i < x2; i++) {
        for (int j=y1; j < y2; j++) {
          grid[i][j] = true;
        }
      }
    }

    int ans = 0;
    for (int i=0; i < 500; i++) {
      for (int j=0; j < 500; j++) {
        if (grid[i][j] == true) {
          ans++;
        }
      }
    }

    cout << ans << endl;
  }












  return 0;
}
