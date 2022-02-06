#include <bits/stdc++.h>

using namespace std;

int main() {
  int lights, total_len, wait_time=0, light_dist, on_time, off_time;
  int check_low, check_high;

  cin >> lights >> total_len;

  for (int i=0; i < lights; i++) {
    cin >> light_dist >> on_time >> off_time;

    check_low = on_time;
    check_high = check_low + off_time;

    while (true) {
      // cout << check_low << endl;
      // cout << check_high << endl;
      // cout << light_dist + wait_time << endl;


      if ((light_dist + wait_time) < check_low) {
        wait_time += check_low - (light_dist + wait_time);
      }
      if ((light_dist + wait_time) < check_high) {
        break;
      } else {
        check_low = check_high + on_time;
        check_high = check_low + off_time;
      }
    }
    // cout << "curr wait:" << wait_time << endl;
  }

  cout << total_len + wait_time << endl;


  return 0;
}
