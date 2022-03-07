#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> gallery;
vector<vector<vector<int>>> mydp;

// a num closed
// b num rooms
// c open / closed
// 0 open
// 1 right closed
// 2 left closed
int dp(int num_closed, int row, int open) {
    if (num_closed == 0) { // closed all needed
      return 0;
    }

    if (row <= -1) { // invalid
      return 300000;
    }

    if (mydp[num_closed][row][open] > -1) { // memoize
      return mydp[num_closed][row][open];
    }

    // for (auto a : mydp) {
    //   for (auto b : a) {
    //     for (auto c : b) {
    //       cout << c << " ";
    //     }
    //     cout << endl;
    //   }
    //   cout << endl;
    // }

    int res = dp(num_closed, row - 1, 0);

    switch (open) {
        case 1: // right closed
        {
            res = min(res, dp(num_closed - 1, row - 1, 1) + gallery[row][1]);
            break;
        }
        case 2: // left closed
        {
            res = min(res, dp(num_closed - 1, row - 1, 2) + gallery[row][0]);
            break;
        }
        case 0: // rooms open
        {
          int close_right = dp(num_closed - 1, row - 1, 1) + gallery[row][1];
          int close_left = dp(num_closed - 1, row - 1, 2) + gallery[row][0];
          res = min(res, min(close_right, close_left));
          break;
        }
    }
    return mydp[num_closed][row][open] = res;
}

int main() {
    int num_rows, num_closed;
    long long sum;

    cin >> num_rows >> num_closed;


    while (num_rows + num_closed != 0) {
      // cout << num_rows << " | " << num_closed << endl;
        sum = 0;
        gallery = vector<vector<int>>(num_rows, vector<int>(2));

        // for (auto r : gallery) {
        //   for (auto c : r) {
        //     cout << c << " ";
        //   }
        //   cout << endl;
        // }

        mydp = vector<vector<vector<int>>>(num_closed + 1,
                      vector<vector<int>>(num_rows,
                             vector<int>(3, -1)));

        // for (auto a : mydp) {
        //   for (auto b : a) {
        //     for (auto c : b) {
        //       cout << c << " ";
        //     }
        //     cout << endl;
        //   }
        //   cout << endl;
        // }

        for (int i = 0; i < num_rows; i++) {
            cin >> gallery[i][0] >> gallery[i][1];
            sum += gallery[i][0] + gallery[i][1];
        }

        // for (auto r : gallery) {
        //   for (auto c : r) {
        //     cout << c << " ";
        //   }
        //   cout << endl;
        // }

        cout << sum - dp(num_closed, num_rows - 1, 0) << endl;

        // for (auto r : gallery) {
        //   for (auto c : r) {
        //     cout << c << " ";
        //   }
        //   cout << endl;
        // }
        // for (auto a : mydp) {
        //   for (auto b : a) {
        //     for (auto c : b) {
        //       cout << c << " ";
        //     }
        //     cout << endl;
        //   }
        //   cout << endl;
        // }

        cin >> num_rows >> num_closed;
    }

    return 0;
}
