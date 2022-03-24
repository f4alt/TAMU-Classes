#include <bits/stdc++.h>

using namespace std;

struct node {
  int value = -1;
  int deg = 0;
  vector<int> adj;
  vector<int> weight;
};

vector<node> v;
vector<int> order;
int next;
queue<int> q;

void check(int num_nodes, int start) {

}

// BFS (usually for shortest path)
// distance is not based on edge distance 'weight'
// void BFS(int num_nodes, int start) {
void BFS() {
  int a, b;

  // init node 1 as distance 0
  // v[start].value = 1;

  // using queue
  // queue<int> q;
  // q.push(start);

  // optional 'time' to keep track of order we encounter each node
  // int time = 0;
  while (!q.empty()) {
    a = q.front();
    q.pop();
    order.push_back(a);
    // time++;
    // cout << "encountered node " << a << " at time " << time << endl;
    for (int i=0; i < v[a].adj.size(); i++) {
      b = v[a].adj[i];
      v[b].deg--;
      if (v[b].deg == 0) { // if not visited yet
        // v[b].value = v[a].value + 1;  // distance is one away from current
        // order.push_back(b);
        q.push(b);
      }
    }
  }
}

int main() {
  int n, k, a, b, w;

  // number of nodes
  cin >> n;
  v.resize(n+1);

  // number of connections
  cin >> k;
  for (int i=0; i < k; i++) {
    // in form of "leftNode rightNode weight"
    cin >> a >> b;
    v[a].adj.push_back(b);
    v[b].deg++;

    // if not directed graph:
    // v[b].adj.push_back(a);
    // v[b].weight.push_back(w);
  }

  // BFS / DFS using 'n' nodes, starting at 'start'
  int start = 1;
  int stacks = 0;
  // queue<int> q;
  for (int i=1; i <= n; i++) {
    if (v[i].deg == 0) {
      // cout << "pushing:" << i << endl;
      // BFS(n, i);
      // start = i;
      // stacks++;
      q.push(i);
    }
  }

  BFS();

  // while (!q.empty()) {
  //   int b = q.front();
  //   q.pop();
  //   order.push_back(b);
  //
  //   for (int i=0; i < v[b].adj.size(); i++) {
  //     v[b].deg--;
  //     if (v[b].deg == 0) {
  //       q.push(i);
  //     }
  //   }
  // }

  // cout << order.size() << endl;

  if (order.size() != n) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    // cout << start << endl;
    for (int i=0; i < order.size(); i++) {
      cout << order[i] << endl;
    }
  }

  // for (int i=1; i <= n; i++) {
  //   cout << "distance of node " << i << " from " << start << " is " << v[i].value << endl;
  // }

  return 0;
}
