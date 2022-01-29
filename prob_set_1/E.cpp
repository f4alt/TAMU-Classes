#include <bits/stdc++.h>

using namespace std;

int main() {
  string temp ="";
  int movx=0, movy=0;
  pair<int, int> xbounds(0,0);
  pair<int, int> ybounds(0,0);
  vector<pair<int, int>> moves;
  std::vector<pair<int, int>>::iterator it;
  bool found;

  while (!cin.eof()) {
    if (temp == "down") {

      movy--;
      if (movy < 0) {
        ybounds.first = min(ybounds.first--, movy);
      }
    }
    else if (temp == "up") {

      movy++;
      if (movy > 0) {
        ybounds.second = max(ybounds.second++, movy);
      }
    }
    else if (temp == "left") {
      movx--;
      if (movx < 0) {
        xbounds.first = min(xbounds.first--, movx);
      }
    }
    else if (temp == "right") {
      movx++;
      if (movx > 0) {
        xbounds.second = max(xbounds.second++, movx);
      }
    }

    moves.push_back(make_pair(movx, movy));
    cin >> temp;
  }

  int origin_x = xbounds.first * -1 +1;
  int origin_y = ybounds.second +1;

  // draw
  for (int i=0; i < ybounds.second - ybounds.first + 3; i++) {
    for (int j=0; j < xbounds.second - xbounds.first + 3; j++) {
      found = false;
        if (i == 0 || i == ybounds.second - ybounds.first + 2 || j == 0 || j == xbounds.second - xbounds.first + 2) {
          cout << "#";
          found = true;
        }
        else if (j == origin_x && i == origin_y) {
          cout << "S";
          found = true;
        }
        else if (j == origin_x + movx && i == origin_y - movy) {
          cout << "E";
          found = true;
        }
      for (it = moves.begin(); it != moves.end(); it++) {
        if (!found && it->first == j-origin_x && it->second == origin_y-i) {
          cout << "*";
          found = true;
          break;
        }
      }
      if (!found) {
        cout << " ";
      }
    }
    cout << endl;
  }
  // cout << endl;
  // cout << movx << endl;
  // cout << movy << endl;
  // cout << endl;
  // cout << xbounds.first << " | " << xbounds.second << endl;
  // cout << ybounds.first << " | " << ybounds.second << endl;
  // cout << endl;
  // for (int i=0; i < moves.size(); i++) {
  //   cout << moves[i].first << "," << moves[i].second << endl;
  // }

  return 0;
}
