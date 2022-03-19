#include <bits/stdc++.h>
using namespace std;

int MAX_CLIMBED = 1002;

int main() {
  int tests;
  cin >> tests;

  while(tests--) {
    int num_moves;
    cin >> num_moves;

    vector<int> moves;
    moves.resize(num_moves, -1);

    for(int i = 0; i < num_moves; i++) {
      cin >> moves[i];
    }

    vector<vector<int> > dp;
    vector<vector<int> > direction;

    vector<int> row(MAX_CLIMBED+1, -1);
    // reset
    dp.resize(num_moves+1, row);
    direction.resize(num_moves+1, row);

    dp[num_moves][0] = 0;
     for (int i = num_moves - 1; i >= 0; i--) {
        for (int j = 0; j < MAX_CLIMBED; j++) {
          // cout << moves[i] + j << endl;
          if (moves[i] + j < MAX_CLIMBED &&
              dp[i + 1][moves[i] + j] != -1) {
              dp[i][j] = max(j, dp[i + 1][moves[i] + j]);
              direction[i][j] = 1;
              // ans.append("U");
          }

          if (j - moves[i] >= 0 &&
              dp[i + 1][j - moves[i]] != -1 &&
              (dp[i][j] == -1 || dp[i][j] > dp[i + 1][j - moves[i]])) {
              dp[i][j] = max(j, dp[i + 1][j - moves[i]]);
              direction[i][j] = -1;
              // ans.append("D");
          }
        }
    }

    if (dp[0][0] == -1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        int curr = 0;
        for (int i = 0; i < num_moves; i++) {
          if (direction[i][curr] == 1) {
            cout << "U";
          } else {
            cout << "D";
          }
          curr += moves[i] * direction[i][curr];
        }
        cout << endl;
        // cout << ans << endl;
    }
  }

  return 0;
}
