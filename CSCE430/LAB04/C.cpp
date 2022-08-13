#include <bits/stdc++.h>

using namespace std;

int main() {
  long long test_cases, ferry_len, num_cars, car_len, curr_width;
  string side;

  cin >> test_cases;

  for (int z=0; z < test_cases; z++) {
    cin >> ferry_len >> num_cars;
    ferry_len *= 100;
    queue<pair<long long, string> > queue_L;
    queue<pair<long long, string> > queue_R;
    int trips = 0;
    bool left = true;

    for (int x=0; x < num_cars; x++) {
      cin >> car_len >> side;

      if (side == "left") {
        // queue_L.push(make_pair<long long, string>(car_len, side));
        queue_L.push( { car_len, side } );
      } else {
        // queue_R.push(make_pair<long long, string>(car_len, side));
        queue_R.push( { car_len, side } );
      }
    }

    // cout << queue_L.size() << " | " << queue_R.size() << endl;

    while (!queue_L.empty() || !queue_R.empty()) {
      curr_width = 0;

      if (left) {
        while (!queue_L.empty() && (curr_width + queue_L.front().first) <= ferry_len) {
          curr_width += queue_L.front().first;
          queue_L.pop();
          // cout << "taking left" << " : " << curr_width << " / " << ferry_len << endl;
        }
      } else if (!left) {
        while (!queue_R.empty() && (curr_width + queue_R.front().first) <= ferry_len) {
          curr_width += queue_R.front().first;
          queue_R.pop();
          // cout << "taking right" << " : " << curr_width << " / " << ferry_len << endl;
        }
      }

      left = !left;
      trips++;
    }

    cout << trips << endl;
  }
}
