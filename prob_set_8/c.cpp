#include <bits/stdc++.h>

using namespace std;

struct node {
  int value = -1;
  int deg = 0;
            //  U  D  L  R
  // int adj[4] = {0, 0, 0, 0};
  vector<int> adj = {0, 0, 0, 0};
  vector<int> weight;
};

vector<node> v;
vector<vector<int> > coast;

bool land_neighbor(int i, int j) {
  if (i < 0 || i >= coast.size() || j < 0 || j >= coast[0].size()) {
    return false;
  }
  if (coast[i][j] != 0) {
    return false;
  }
  return true;
}

// BFS (usually for shortest path)
// distance is not based on edge distance 'weight'
void BFS() {
  int a, b;

  // init node 1 as distance 0
  // v[start].value = 0;

  // using queue
  queue<pair<int, int> > q;
  q.push({0, 0});

  // optional 'time' to keep track of order we encounter each node
  // int time = 0;
  while (!q.empty()) {
    a = q.front().first;
    b = q.front().second;
    q.pop();
    // time++;
    // cout << "encountered node " << a << " at time " << time << endl;
    // for (int i=0; i < v[a].adj.size(); i++) {
    //   b = v[a].adj[i];
    //   if (v[b].value == -1) { // if not visited yet
    //     v[b].value = v[a].value + 1;  // distance is one away from current
    //     q.push(b);
    //   }
    // }
    if (coast[a][b] != 0) {
      continue;
    }

    coast[a][b]--;

    // check up
    if (land_neighbor(a+1, b)) {
      q.push({a+1, b});
    }
    // check down
    if (land_neighbor(a-1, b)) {
      q.push({a-1, b});
    }
    // check right
    if (land_neighbor(a, b+1)) {
      q.push({a, b+1});
    }
    // check left
    if (land_neighbor(a, b-1)) {
      q.push({a, b-1});
    }
  }
}

// void DFS(int start) {
//   int a, b;
//
//   // init node 1 as distance 0
//   v[start].value = 0;
//
//   // using stack
//   stack<int> s;
//   s.push(start);
//
//   // optional 'time' to keep track of order we encounter each node
//   // int time = 0;
//   while (!s.empty()) {
//     a = s.top();
//     s.pop();
//     // time++;
//     // cout << "encountered node " << a << " at time " << time << endl;
//     for (int i=0; i < v[a].adj.size(); i++) {
//       b = v[a].adj[i];
//       if (v[b].value == -1) { // if not visited yet
//         v[b].value = v[a].value + 1;  // distance is one away from current
//         s.push(b);
//       }
//     }
//   }
// }

int main() {
  int n, m;
  string temp;

  cin >> n >> m;

  vector<int> line(m+2, 0);
  coast.resize(n+2, line);

  for (int i=1; i <= n; i++) {
    cin >> temp;
    for (int j=0; j < temp.size(); j++) {
      coast[i][j+1] = (int)temp[j]-48;
    }
  }

  // sort input into graph
  // for (int i=1; i < coast.size()-1; i++) {
  //   for (int j=1; j < coast[0].size()-1; j++) {
  //     // check U D L R
  //     if (coast
  //   }
  //   // cout << endl;
  // }
  BFS();

  int total = 0;

  for (int i=1; i < coast.size()-1; i++) {
    for (int j=1; j < coast[0].size()-1; j++) {
      if (coast[i][j] == 1) {

        if (coast[i+1][j] < 0) {
          total++;
        }
        if (coast[i-1][j] < 0) {
          total++;
        }
        if (coast[i][j+1] < 0) {
          total++;
        }
        if (coast[i][j-1] < 0) {
          total++;
        }
      }
    }
  }

  cout << total << endl;

  // test print
  // for (int i=0; i < coast.size(); i++) {
  //   for (int j=0; j < coast[0].size(); j++) {
  // for (int i=1; i < coast.size()-1; i++) {
  //   for (int j=1; j < coast[0].size()-1; j++) {
  //     cout << coast[i][j] << " ";
  //   }
  //   cout << endl;
  // }















  return 0;
}
