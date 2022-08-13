#include <bits/stdc++.h>

using namespace std;

int main() {
  long long wire_len, bird_dist, num_birds, temp, rightmost, leftmost, additional_birds=0;
  priority_queue<long long> pq;

  cin >> wire_len >> bird_dist >> num_birds;
  // wire_len *= 100;

  for (int i=0; i < num_birds; i++) {
    cin >> temp;

    pq.push(temp);
  }



  if (!pq.empty()) {
    rightmost = pq.top();
    while (pq.size() > 1) {
      temp = pq.top();
      pq.pop();
      additional_birds += max((temp - pq.top()) / bird_dist -1, (long long)0);
      // cout << "adding in loop:" << additional_birds << endl;
    }
    leftmost = pq.top();

    // after last bird
    additional_birds += (wire_len -6 - rightmost) / bird_dist;
    // cout << "after last:" << additional_birds << endl;
    // before first bird
    additional_birds += (leftmost -6) / bird_dist;
    // cout << "before first:" << additional_birds << endl;
  } else {
    additional_birds += (wire_len - 6) / bird_dist;
  }



  cout << additional_birds << endl;

}
