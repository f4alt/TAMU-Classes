#include <bits/stdc++.h>

using namespace std;

int main() {
  int qnty = -1;
  string fav = "";
  string temp = "";
  int doubles = 0;
  int fav_doubles = -1;

  // cin >> qnty;

  while (qnty != 0) {
    cin >> qnty;
    if (qnty == 0) {
      break;
    }
    for (int i=0; i < qnty; i++) {
      cin >> temp;

      for (int j=0; j < temp.size(); j++) {
        if (j+1 < temp.size() && (temp[j] == 'a' || temp[j] == 'e' || temp[j] == 'i' || temp[j] == 'o' || temp[j] == 'u' || temp[j] == 'y') &&
        (temp[j+1] == temp[j])) {
          doubles++;
          // j += 2;
        }
      }

      if (doubles > fav_doubles) {
        fav_doubles = doubles;
        fav = temp;
        // cout << "fav:" << fav << " doubles:" << fav_doubles;
      }
      doubles = 0;
    }

    cout << fav << endl;
    fav = "";
    fav_doubles = 0;
    doubles = 0;

  }



}
