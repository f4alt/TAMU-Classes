#include <bits/stdc++.h>

using namespace std;

// D

int main() {
  int loop, len, d_count;
  bool reverse = false;
  string action, list;
  // int input*;

  std::ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> loop;

  for (int i=0; i < loop; i++) {
    cin >> action >> len >> list;

    int input[len];

    for (int i=0; i < len; i++) {
      input[i] = list[2*i+1] - 48;
      // cout << input[i] << " | " << list[2*i+1] << endl;
    }

    // r_count=0;
    d_count=0;
    reverse = false;

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
            // cout << i << endl;
            if (input[i] == -1) {
              continue;
            } else {
              input[i] = -1;
              break;
            }
          }
        } else {
          // cout << "here" << endl;
          for (int i=0; len-1; i++) {
            // cout << i << endl;
            if (input[i] == -1) {
              continue;
            } else {
              input[i] = -1;
              break;
            }
          }
        }
      }
    }
    // simplify requests
    // r_count = r_count % 2;
    //
    string output = "[";

    // cout << "[";
    for (int i=0; i < len; i++) {
      if (input[i] != -1) {
        output.append(to_string(input[i]));
        output.append(",");
        // cout << input[i];
      }
      // if (input[i] != -1 && i != len-1) {
      //   cout << ",";
      // }
    }
    output.erase(output.size()-1);
    output.append("]\n");

    cout << output;
    // cout << "]\n";


    // cout << "do something" << endl;
    // cout << "RCOUNT:" << r_count << " | " << d_count << endl;
  }



  return 0;
}
