#include <bits/stdc++.h>

using namespace std;

int main() {
  int curr_hour, curr_min, curr_sec, det_hour, det_min, det_sec, res_hour, res_min, res_sec;
  string time, temp="";

  // for (int i=0; i < 2; i++) {
    cin >> time;
    sscanf(time.c_str(), "%d:%d:%d", &curr_hour, &curr_min, &curr_sec);
    cin >> time;
    sscanf(time.c_str(), "%d:%d:%d", &det_hour, &det_min, &det_sec);
    // for (int i=0; i < temp.size(); i++) {
    //
    // temp.append((string)time[0]);
    // temp.append(time[1]);
    // temp.append(time[0] + time[1];
    // cout << temp << endl;
    // curr_hour = stoi(temp);
  // }
  res_sec = det_sec - curr_sec;
  if (res_sec < 0) {
    res_sec += 60;
    det_min--;
  }
  res_min = det_min - curr_min;
  if (res_min < 0) {
    res_min += 60;
    det_hour--;
  }
  res_hour = det_hour - curr_hour;
  if (res_hour < 0) {
    res_hour += 24;
  }

  if (res_hour == 0 && res_min == 0 && res_sec == 0) {
    cout << "24:00:00" << endl;
  } else {
    printf("%02d:%02d:%02d\n", res_hour, res_min, res_sec);
  }


  // cout << curr_hour << endl;

  return 0;
}
