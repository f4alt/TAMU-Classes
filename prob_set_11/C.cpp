#include <bits/stdc++.h>

using namespace std;

struct node {
  int value = -1;
  // int deg = 0;
  vector<pair<float, float> > adj;
  // vector<int> weight;
};

// vector<node> v;
vector<pair<float, float> > gophers, holes;
// vector<vector<int>> adj;
vector<bool> visited(200, false);

int pythag(pair<float, float> a, pair<float, float> b) {
  float first = pow(a.first - b.first, 2);
  // cout << first << endl;
  float second = pow(a.second - b.second, 2);
  // cout << second << endl;
  return sqrt(abs(first + second));
  // return (abs(sqrt(pow(a.first - b.first, 2) - pow(a.second - b.second, 2))));
}

// BFS (usually for shortest path)
// distance is not based on edge distance 'weight'
void BFS(int start) {
  int a, b;

  // init node 1 as distance 0
  // v[start].value = 0;

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
    // for (int i=0; i < v[a].adj.size(); i++) {
    //   b = v[a].adj[i];
    //   if (v[b].value == -1) { // if not visited yet
    //     v[b].value = v[a].value + 1;  // distance is one away from current
    //     q.push(b);
    //   }
    // }
  }
}

void DFS(int start) {
  int a, b;

  // init node 1 as distance 0
  // v[start].value = 0;

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
    // for (int i=0; i < v[a].adj.size(); i++) {
    //   b = v[a].adj[i];
    //   if (v[b].value == -1) { // if not visited yet
    //     v[b].value = v[a].value + 1;  // distance is one away from current
    //     s.push(b);
    //   }
    // }
  }
}

int solve(int i,
            vector<vector<int>> &graph,
            vector<int> &match) {
    if (visited[i]) {
      return 0;
    }

    visited[i] = true;

    for (int j = 0; j < graph[i].size(); j++) {
        int n = graph[i][j];
        if (match[n] == -1 || solve(match[n], graph, match)) {
            match[n] = i;
            return 1;
        }
    }
    return 0;
}

int main() {
  int n, m, s, v;
  float x, y;

  while (cin >> n >> m >> s >> v) {
    // cin >> n >> m >> s >> v;

    // gophers.resize(n);
    // holes.resize(m);

    // coordinates gophers
    for (int i=0; i < n; i++) {
      cin >> x >> y;
      // gophers[i].first = x;
      // gophers[i].second = y;
      gophers.push_back( { x, y } );
    }

    // coordinates holes
    for (int i=0; i < m; i++) {
      cin >> x >> y;
      // holes[i].first = x;
      // holes[i].second = y;
      holes.push_back( { x, y } );
    }

    // int max_dist = s * v;
    vector<int> match(n + m, -1);
    vector<vector<int>> adj(n + m);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        // cout << pythag(gophers[i], holes[j]) << endl;
        if (pythag(gophers[i], holes[j]) / v < s) {
          adj[i].push_back(n + j);
          adj[n + j].push_back(i);
        }
      }
    }

    int ans = 0;
    // int ans = kuhn(n, m, adj);
    for (int i=0; i < n; i++) {
      visited.clear();
      visited.resize(200, false);
      ans += solve(i, adj, match);
    }

    cout << n - ans << endl;

    gophers.clear();
    holes.clear();
    visited.clear();
    visited.resize(200, false);
  }












  return 0;
}
