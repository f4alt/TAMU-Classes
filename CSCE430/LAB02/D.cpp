#include <bits/stdc++.h>

using namespace std;

int main() {
  int check_val;
  pair<int, int> launch;
  launch.first = 4;
  launch.second = 2018;

  cin >> check_val;



  while (check_val >= launch.second) {
    if (launch.second == check_val) {
      cout << "yes" << endl;
      return 0;
    }
    
    launch.first += 2;
    if (launch.first > 12) {
      launch.first -= 12;
      launch.second ++;
    }

    launch.second += 2;

    // cout << launch.second << " | " << check_val << endl;
    // if (launch.second == check_val) {
    //   cout << "yes" << endl;
    //   return 0;
    // }
    // cout << "adding:" << floor((launch.first + 26) / 12) << endl;
    // launch.second = launch.second + floor((launch.first + 26) / 12);
    // launch.first = launch.first % 26;
    // if (launch.first == 0) {
    //   launch.second++;
    // }
    // // launch.second = launch.second + floor(launch.second / 26);
    // cout << launch.second << " | " << check_val << endl;
    if (launch.second == check_val) {
      cout << "yes" << endl;
      return 0;
    }

  }
  cout << "no" << endl;
}
