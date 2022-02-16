#include <bits/stdc++.h>

using namespace std;

int main() {
  long long additional_birds=0, wire_len, bird_dist, curr_sitting, temp, wire_start, wire_end, check_pos;

  cin >> wire_len >> bird_dist >> curr_sitting;

  wire_end = wire_len - 6;
  wire_start = 6;

  priority_queue<long long> starting_birds;
  for (int i=0; i < curr_sitting; i++) {
    cin >> temp;

    starting_birds.push(temp);
  }

  if (!starting_birds.empty()) {
    additional_birds = (wire_end - starting_birds.top()) / bird_dist;
    check_pos = starting_birds.top();
    starting_birds.pop();
  } else {
    check_pos = wire_end;
    additional_birds++;
  }


  while (!starting_birds.empty()) {
    // cout << check_pos << " | " << starting_birds.top() << endl;
    // if (check_pos > (starting_birds.top() + bird_dist)) {
    //   additional_birds++;
    //   check_pos -= bird_dist;
    // } else {
    //   check_pos = starting_birds.top() - bird_dist;
    //   starting_birds.pop();
    // }

    long long left = starting_birds.top();
    starting_birds.pop();
    if (starting_birds.empty()) {
      break;
    }
    check_pos = starting_birds.top();

    additional_birds += (check_pos - left) / bird_dist;

    cout << "*" << additional_birds << endl;
    // cout << starting_birds.size() << endl;
  }
  // check_pos = starting_birds.top();
  // cout << check_pos << endl;
  check_pos -= bird_dist;
  while (check_pos >= wire_start) {
    // cout << check_pos << endl;
    additional_birds++;
    check_pos -= bird_dist;
  }

  cout << additional_birds << endl;
}
