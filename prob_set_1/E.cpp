#include <bits/stdc++.h>

using namespace std;

int main() {
  string temp ="";
  int xmin, xmax, ymin, ymax;
  xmin = xmax = ymin = ymax = 0;
  int movx=0, movy=0;
  pair<int, int> xbounds(0,0);
  pair<int, int> ybounds(0,0);
  int delt_x =0;
  int delt_y =0;

  while (!cin.eof()) {
    if (temp == "down") {

      movy--;
      if (ybounds.second == 0) {
        ybounds.first--;
      }

      cout << "down:" << movy << endl;
    }
    else if (temp == "up") {

      movy++;
      if (ybounds.first == 0) {
        ybounds.second++;
      }
      cout << "up:" << movy << endl;
    }
    else if (temp == "left") {
      movx--;
      if (xbounds.second == 0) {
        xbounds.first--;
      }

      cout << "left:" << movx << endl;
    }
    else if (temp == "right") {
      movx++;
      if (xbounds.first == 0) {
        xbounds.second++;
      }

      cout << "right:" << movx << endl;
    }

    cin >> temp;
  }
  // cout << xmax << endl;
  // cout << xmin << endl;
  // cout << ymax << endl;
  // cout << ymin << endl;
  // cout << movx << endl;
  // cout << movy << endl;
  cout << xbounds.first << " | " << xbounds.second << endl;
  cout << ybounds.first << " | " << ybounds.second << endl;
  // cout << xbounds.second - xbounds.first << endl;
  // cout << ybounds.second - ybounds.first << endl;

  return 0;
}
