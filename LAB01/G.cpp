#include <bits/stdc++.h>

using namespace std;

int main() {
  int leave_time, start_time, n_routes;

  cin >> leave_time >> start_time >> n_routes;

  int walk_arr[n_routes], bus_arr[n_routes], bus_sched_arr[n_routes];
  int temp_in;

  // take all input
  for (int i=0; i < n_routes+1; i++) {
      cin >> temp_in;
      walk_arr[i] = temp_in;
  }
  for (int i=0; i < n_routes; i++) {
      cin >> temp_in;
      bus_arr[i] = temp_in;
  }
  for (int i=0; i < n_routes; i++) {
      cin >> temp_in;
      bus_sched_arr[i] = temp_in;
  }

  int total_time = leave_time;
  for (int i=0; i < n_routes; i++) {
    total_time += walk_arr[i];
    // cout << "walk total: " << total_time << endl;
    // cout << "waiting:" << bus_sched_arr[i] - total_time % bus_sched_arr[i] << endl;
    if (total_time%bus_sched_arr[i] != 0) {
      total_time += (bus_sched_arr[i] - (total_time%bus_sched_arr[i]));
    }
    // cout << "wait total: " << total_time << endl;
    total_time += bus_arr[i];
    // cout << "bus total: " << total_time << endl;

  }
  total_time += walk_arr[n_routes];

  // cout << "total time:" << total_time << endl;

  if (total_time > start_time) {
    cout << "no" << endl;
  } else {
    cout << "yes" << endl;
  }

  return 0;
}
