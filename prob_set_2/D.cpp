#include <bits/stdc++.h>

using namespace std;

// A

int main() {
  int loop, len, d_count;
  bool reverse = false;
  string action, list;


  std::ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> loop;

  for (int i=0; i < loop; i++) {
    cin >> action >> len >> list;

    int input[len] = {-1};

    for (int i=0; i < len; i++) {
      input[i] = list[2*i+1] - 48;
      // cout << input[i] << " | " << list[2*i+1] << endl;
    }

    // r_count=0;
    d_count=0;

    for (int i=0; i < action.size(); i++) {
      if (action[i] == 'R' && i+1 < action.size()-1 && action[i+1] != 'R') {
        reverse = !reverse;
        // cout << "reversing" << endl;
      } else if (action[i] == 'D') {
        d_count++;
        if (d_count > len) {
          cout << "error" << endl;
          break;
        }
        if (reverse) {
          for (int i=len-1; i > 0; i--) {
            cout << i << endl;
            if (action[i] == -1) {
              continue;
            } else {
              action[i] = -1;
              break;
            }
          }
        }
      }
    }
    // simplify requests
    // r_count = r_count % 2;

    cout << "[";
    for (int i=0; i < len; i++) {
      if (input[i] != -1) {
        cout << input[i];
      }
      if (i != len-1) {
        cout << ",";
      }
    }
    cout << "]\n";


    // cout << "do something" << endl;
    // cout << "RCOUNT:" << r_count << " | " << d_count << endl;
  }



  return 0;
}
