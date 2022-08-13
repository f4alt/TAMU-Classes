#include <bits/stdc++.h>

using namespace std;

int main() {
  int take=0, drop=0;
  int moves;
  string action;
  int move_qnty;

  cin >> moves;
  while (moves != 0) {

    for (int i=0; i < moves; i++) {
      cin >> action >> move_qnty;
      if (action == "DROP") {
        drop += move_qnty;
        cout << "DROP 2 " << move_qnty << endl;
      }
      if (action == "TAKE") {
        if (take < move_qnty) {
          cout << "MOVE 2->1 " << drop << endl;
          take = drop;
          drop = 0;
        }
        cout << "TAKE 1 " << move_qnty << endl;
        take -= move_qnty;
      }
    }
    // end sequence, reset everything
    cout << endl;
    cin >> moves;
    take =0;
    drop =0;
  }


  return 0;
}
