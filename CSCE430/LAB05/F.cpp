#include <bits/stdc++.h>

using namespace std;

int main() {
  long long queries, ships, temp, move_tot=0;
  priority_queue<long long> moves;

  cin >> queries >> ships;

  while (queries--) {
    cin >> temp;
    moves.push(-temp);
  }

  while (ships > 0 && !moves.empty()) {
    // cout << ships << " - " << moves.top() -1 << endl;
    ships += moves.top() - 1;
    moves.pop();
    // cout << "*" << ships << endl;
    if (ships < 0) {
      break;
    }
    move_tot++;
  }

  cout << move_tot << endl;


  return 0;
}
