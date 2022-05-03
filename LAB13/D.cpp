#include <bits/stdc++.h>

using namespace std;

int main() {
  string in;
  map<char, int> capitals;

  cin >> in;

  char temp;
  char last_cap = in[0];
  char maxPos = in[0];
  int maxAmt = 0;
  int ans = 0;
  int rt = 0;
  for (int i=1; i < in.size(); i++) {
    temp = in[i];

    if (isupper(temp)) {
      if (rt == 0) {
        ans += 3;
        // maxAmt = 3;
        // cout << temp << " 1adding 3" << endl;
      } else if (rt <= 3) {
        ans += 3 - rt;
        // if ((3-rt) > maxAmt) {
        //   maxAmt = (3-rt);
        // }
        // cout << temp << " 2adding " << 3 - rt << endl;
      } else {
        rt -= 3;
        while (rt > 4) {
          rt -= 4;
        }
        ans += 4 - rt;
      }

      rt = 0;
    } else {
      rt ++;
    }
  }

  cout << ans << endl;





  return 0;
}
