#include <bits/stdc++.h>

using namespace std;

int main() {
  int num_players, moves, priority, ladder;
  // move priority , move idx
  priority_queue<pair<int, int>> move_order;

  cin >> num_players >> moves;

  int final[num_players];

  for (int i=0; i < num_players; i++) {
    final[i] = i;
  }

  for (int z=0; z < moves; z++) {

    cin >> ladder >> priority;

    move_order.push({ priority, ladder });
  }

  while (!move_order.empty()) {
    // cout << "top:" << move_order.top().first << " | " << move_order.top().second << endl;
    int swap1 = move_order.top().second;
    move_order.pop();

    int temp = final[swap1];
    final[swap1] = final[swap1 + 1];
    final[swap1 + 1] = temp;
  }

  for (int i=0; i < num_players; i++) {
    cout << final[i] << " ";
  }
  cout << endl;



  return 0;
}
