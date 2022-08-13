#include <bits/stdc++.h>

using namespace std;

struct node {
  int value = -1;
  vector<int> adj;
  vector<int> weight;
  bool visited = false;
};

vector<node> v;

// BFS (usually for shortest path)
// distance is not based on edge distance 'weight'
// void BFS(int num_nodes, int start) {
//   int a, b;
//   // init all to -1
//   for (int i=1; i <= num_nodes; i++) {
//     v[i].value = -1;
//   }
//   // init node 1 as distance 0
//   v[start].value = 0;
//   queue<int> q;
//   q.push(start);
//   // int time = 0; // order that we encounter each node
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

bool check(int num_nodes, int start) {
  v[start].visited = false;
  int b;

  for (int i=0; i < v[start].adj.size(); i++) {
    b = v[start].adj[i];
    if (v[b].value == v[start].value) {
      return false;
    }
  }

  return true;
}

void DFS(int num_nodes, int start, int val) {
  v[start].visited = true;

  int a, b;
  // init all to -1
  // for (int i=1; i <= num_nodes; i++) {
  //   v[i].value = -1;
  // }
  // init node 1 as distance 0
  v[start].value = val;
  stack<int> s;
  s.push(start);
  // int time = 0; // order that we encounter each node
  for (int i=0; i < v[start].adj.size(); i++) {
    b = v[start].adj[i];
    // cout << "b:" << b << endl;
    if (v[b].visited != true) {
      if (val == 0) {
        DFS(num_nodes, b, 1);
      } else if (val == 1) {
        DFS(num_nodes, b, 0);
      }
    }
  }
  // while (!s.empty()) {
  //   a = s.top();
  //   s.pop();
  //   // time++;
  //   // cout << "encountered node " << a << " at time " << time << endl;
  //   for (int i=0; i < v[a].adj.size(); i++) {
  //     b = v[a].adj[i];
  //     cout << "b:" << b << endl;
  //     if (v[b].value == -1) { // if not visited yet
  //       // v[b].value = v[a].value + 1;  // distance is one away from current
  //       if (val == 1) {
  //         DFS(num_nodes, i, 2);
  //       } else if (val == 2) {
  //         DFS(num_nodes, i, 1);
  //       }
  //       s.push(b);
  //     }
  //   }
  // }
}

int main() {
  int n, k, w;
  string temp, a, b;
  map<string, int> forward;
  map<int, string> reverse;

  cin >> n;
  v.resize(n+1);

  // read in all items
  for (int i=0; i < n; i++) {
    cin >> temp;
    forward[temp] = i;
    reverse[i] = temp;
  }

  // read in restrictions
  cin >> k;
  for (int i=0; i < k; i++) {
    cin >> a >> b;
    int aa, bb;
    aa = forward[a];
    bb = forward[b];

    v[aa].adj.push_back(bb);
    v[bb].adj.push_back(aa);
  }

  // assign possibilities
  for (int i=0; i < n; i++) {
    if (v[i].visited == false) {
      DFS(n, i, 0);
    }
  }

  // check good assignment
  bool good = true;
  for (int i=0; i < n; i++) {
    if (v[i].visited == true) {
      good &= check(n, i);
    }
  }

  if (!good) {
    cout << "impossible" << endl;
  } else {
    for (int i=0; i < n; i++) {
      if (v[i].value == 0) {
        cout << reverse[i] << " ";
      }
    }
    cout << endl;
    for (int i=0; i < n; i++) {
      if (v[i].value == 1) {
        cout << reverse[i] << " ";
      }
    }
    cout << endl;
  }
  // test output
  // for (int i=0; i < n; i++) {
  //   cout << "v[" << reverse[i] << "]:";
  //   for (int j=0; j < v[i].adj.size(); j++) {
  //     cout << reverse[v[i].adj[j]] << " ";
  //   }
  //   cout << endl;
  // }
  // for (int i=0; i < n; i++) {
  //   cout << "v[" << reverse[i] << "]:" << v[i].value << endl;
  // }













  return 0;
}
