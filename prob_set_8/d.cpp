#include <bits/stdc++.h>

using namespace std;

char board[51][51];
bool movable[51][51];

int h, w;
int h_moves[] = {1, 0, -1, 0};
int w_moves[] = {0, 1, 0, -1};
int ans = 0;

struct node {
  int value = -1;
  int deg = 0;
  vector<int> adj;
  vector<int> weight;
};

vector<node> v;

// BFS (usually for shortest path)
// distance is not based on edge distance 'weight'
// void BFS(int start) {
//   int a, b;
//
//   // init node 1 as distance 0
//   v[start].value = 0;
//
//   // using queue
//   queue<int> q;
//   q.push(start);
//
//   // optional 'time' to keep track of order we encounter each node
//   // int time = 0;
//   while (!q.empty()) {
//     a = q.front();
//     q.pop();
//     // time++;
//     // cout << "encountered node " << a << " at time " << time << endl;
//     for (int i=0; i < v[a].adj.size(); i++) {
//       b = v[a].adj[i];
//       if (v[b].value == -1) { // if not visited yet
//         v[b].value = v[a].value + 1;  // distance is one away from current
//         q.push(b);
//       }
//     }
//   }
// }

void DFS(int i, int j){
  int a, b;

  // init node 1 as distance 0
  // v[start].value = 0;
  //
  // // using stack
  // stack<int> s;
  // s.push(start);
  if (board[i][j] == '#') {
    return;
  }

  if (board[i][j] == 'G') {
    ans++;
  }

  board[i][j] = '#';

  if (movable[i][j]) {
    for (int k = 0; k < 4; k++ ) {
      a = i + h_moves[k];
      b = j + w_moves[k];

      if (a < h && a >= 0 && b < w && b >= 0) {
        DFS(a, b);
      }
    }
  }
}




int main(){
    int start_h, start_w;
    memset(board, '#', sizeof(board));
    memset(movable, true, sizeof(movable));

    cin >> w >> h;

    for (int i=0; i < h; i++) {
      cin >> board[i];
    }

    // for (int i=0; i < h; i++) {
    //   for (int j=0; j < w; j++) {
    //     cout << board[i][j];
    //   }
    //   cout << endl;
    // }


    for (int i=0; i < h; i++) {
      for (int j=0; j < w; j++) {
        for (int k=0; k < 4; k++) {
          start_h = i + h_moves[k];
          start_w = j + w_moves[k];
          if (start_h < h && start_h >= 0 && start_w < w && start_w >= 0 && board[start_h][start_w] == 'T') {
            movable[i][j] = false;
          }
        }
      }
    }


    for (int i=0; i < h; i++) {
      for (int j=0; j < w; j++) {
        if (board[i][j] == 'T') {
          board[i][j] = '#';
        } else if (board[i][j] == 'P') {
          start_h = i;
          start_w = j;
        }
      }
    }

    // for (int i=0; i < h; i++) {
    //   for (int j=0; j < w; j++) {
    //     cout << board[i][j];
    //   }
    //   cout << endl;
    // }

    DFS(start_h, start_w);

    cout << ans << endl;










	return 0;
}
