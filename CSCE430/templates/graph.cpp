#include <bits/stdc++.h>

using namespace std;

struct node {
  int value = -1;
  int deg = 0;
  vector<int> adj;
  vector<int> weight;
};

vector<node> v;

// BFS (usually for shortest path)
// distance is not based on edge distance 'weight'
void BFS(int start) {
  int a, b;

  // init node 1 as distance 0
  v[start].value = 0;

  // using queue
  queue<int> q;
  q.push(start);

  // optional 'time' to keep track of order we encounter each node
  // int time = 0;
  while (!q.empty()) {
    a = q.front();
    q.pop();
    // time++;
    // cout << "encountered node " << a << " at time " << time << endl;
    for (int i=0; i < v[a].adj.size(); i++) {
      b = v[a].adj[i];
      if (v[b].value == -1) { // if not visited yet
        v[b].value = v[a].value + 1;  // distance is one away from current
        q.push(b);
      }
    }
  }
}

void DFS(int start) {
  int a, b;

  // init node 1 as distance 0
  v[start].value = 0;

  // using stack
  stack<int> s;
  s.push(start);

  // optional 'time' to keep track of order we encounter each node
  // int time = 0;
  while (!s.empty()) {
    a = s.top();
    s.pop();
    // time++;
    // cout << "encountered node " << a << " at time " << time << endl;
    for (int i=0; i < v[a].adj.size(); i++) {
      b = v[a].adj[i];
      if (v[b].value == -1) { // if not visited yet
        v[b].value = v[a].value + 1;  // distance is one away from current
        s.push(b);
      }
    }
  }
}

int main() {
  int n, k, a, b, w;

  // number of nodes
  cin >> n;
  v.resize(n+1);

  // read in values per node
  for (int i=0; i < n; i++) {
    // cin >> v[i].value;
  }

  // number of connections
  cin >> k;
  for (int i=0; i < k; i++) {
    // in form of "leftNode rightNode weight"
    cin >> a >> b >> w;
    v[a].adj.push_back(b);
    v[a].weight.push_back(w);

    // if not directed graph:
    v[b].adj.push_back(a);
    v[b].weight.push_back(w);
  }

  // BFS / DFS using 'n' nodes, starting at 'start'
  int start = 1;
  BFS(start);
  DFS(start);

  // test output
  for (int i=1; i <= n; i++) {
    cout << "distance of node " << i << " from " << start << " is " << v[i].value << endl;
  }

  return 0;
}
