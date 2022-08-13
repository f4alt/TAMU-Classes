#include <bits/stdc++.h>

using namespace std;

int n, k, ans=0;
vector<string> board;
vector<int> ships;
vector<vector<int> > placement;

void check_sol(int x) {
  for (int i=1; i <= n; i++) {
    for (int j=1; j <= n; j++) {
      if (board[i][j-1] == 'O' && placement[i][j] == 0) {
        return;
      }
    }
  }
  ans++;
}

void recurs(int x) {
  if (x > k) {
    check_sol(x);
    return;
  }

  int ship_len = ships[x];

  // check vertical
  for (int i=1; i <= n; i++) {
    int check=0;
    for (int j=1; j <= n; j++) {
      if (placement[i][j] == 0) {
        check++;

        if (check == ship_len) {
          for (int z=j; z > j-check; z--) {
            placement[i][z] = x;
          }

          recurs(x+1);

          for (int z=j; z > j-check; z--) {
            placement[i][z] = 0;
          }

          j = j-check+1;
          check=0;
        }
      }
      else check = 0;
    }
  }

  // for (int i=1; i <= n; i++) {
  //   for (int j=1; j <= n; j++) {
  //     cout << placement[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  // cout << endl;

  if (ship_len == 1) return;

  // check horizontal
  for (int j=1; j <=n; j++) {
    int check=0;
    for (int i=1; i <= n; i++) {
      if (placement[i][j] == 0) {
        check++;
        if (check == ship_len) {
          for (int z=i; z > i - check; z--) {
            placement[z][j] = x;
          }
          recurs(x+1);
          for (int z=i; z > i - check; z--) {
            placement[z][j] = 0;
          }
          i = i - check +1;
          check = 0;
        }
      }
      else check = 0;
    }
  }

  // for (int i=1; i <= n; i++) {
  //   for (int j=1; j <= n; j++) {
  //     cout << placement[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  // cout << endl;
}

int main() {
  string temp;
  cin >> n >> k;

  board.resize(n+1);
  placement.resize(n+1, vector<int>(n+1, 0));
  ships.resize(k+1);

  for (int i=1; i <= n; i++) {
    cin >> temp;
    // cin >> board[i];
    // cout << temp << endl;
    board[i] = temp;
  }

  // for (int i=1; i <= n; i++) {
  //   cout << board[i] << endl;
  // }

  for (int i=1; i <= k; i++) {
    cin >> ships[i];
  }

  // for (int i=1; i <= k; i++) {
  //   cout << ships[i] << endl;
  // }

  for (int i=1; i <= n; i++) {
    for (int j=1; j <= n; j++) {
      if (board[i][j-1] == 'X') {
        placement[i][j] = -1;
      }
    }
  }


  recurs(1);

  cout << ans << endl;











  return 0;
}
