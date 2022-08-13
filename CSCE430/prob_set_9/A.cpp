#include <bits/stdc++.h>

using namespace std;

struct node {
  int value = -1;
  int d;
  int low;
  int time;
  vector<int> adj;
};

vector<node> v;
vector<vector<int> > adj;
vector<pair<int, int> > bridges;
vector<bool> vis;
vector<int> par;
vector<int> d;
vector<int> low;
set<pair<int,int>> skip;

int dfstime = 0;

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

void find(int curr) {
    vis[curr] = true;
    d[curr] = low[curr] = ++dfstime;
    for(auto next : adj[curr]) {
        if(!vis[next]) {
            par[next] = curr;
            find(next);
            low[curr] = min(low[curr], low[next]);
            if(low[next] > d[curr]) {
                bridges.push_back({next,curr});
            }
        }
        else if(next != par[curr]) {
            low[curr] = min(low[curr], d[next]);
        }
    }
}

int dfs(int curr) {
    vis[curr] = true;
    int total = 1;

    for(auto next : adj[curr]) {
        if(vis[next]) {
            continue;
        }

        if(skip.count({curr,next}) || skip.count({next,curr})) {
            continue;
        }

        total += dfs(next);
    }
    return total;
}


void DFS(int start) {
  int a, b;
  // optional 'time' to keep track of order we encounter each node
  int time = 0;

  // init node 1 as distance 0
  v[start].value = 0;
  v[start].time = time;

  // using stack
  stack<int> s;
  s.push(start);

  while (!s.empty()) {
    a = s.top();
    s.pop();
    time++;
    // cout << "encountered node " << a << " at time " << time << endl;
    for (int i=0; i < v[a].adj.size(); i++) {
      b = v[a].adj[i];
      if (v[b].value == -1) { // if not visited yet
        v[b].value = v[a].value + 1;  // distance is one away from current
        v[a].low = min(v[a].low, v[b].low);
        v[b].time = time;
        s.push(b);
      }
    }
  }
}

int main() {
  int n, k, a, b, w;

  while (cin >> n >> k && n + k > 0) {
    // number of nodes
    // cin >> n;
    v.clear();
    adj.clear();
    v.resize(n+1);
    adj.resize(n);

    // read in values per node
    // for (int i=0; i < n; i++) {
      // cin >> v[i].value;
    // }

    // number of connections
    // cin >> k;
    for (int i=0; i < k; i++) {
      // in form of "leftNode rightNode weight"
      cin >> a >> b;
      adj[a].push_back(b);
      // v[a].weight.push_back(w);

      // if not directed graph:
      adj[b].push_back(a);
      // v[b].weight.push_back(w);
    }

    vis.clear();
    par.clear();
    d.clear();
    low.clear();
    vis.resize(n, false);
    par.resize(n, -1);
    d.resize(n, -1);
    low.resize(n, -1);

    find(0);

    for(auto i : bridges) {
        skip.insert(i);
    }

    // cout << "bridges:" << bridges.size() << endl;

    for(int i = 0; i < n; i++) {
        vis[i] = false;
    }

    int cycles = dfs(0);

    if (cycles != n) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }

    // cout << dfs(0) << endl;



    // BFS / DFS using 'n' nodes, starting at 'start'
    int start = 0;
    // BFS(start);
    // DFS(start);

    // test output
    // for (int i=0; i < n; i++) {
    //   cout << "node " << i << ": time | d | low => " << v[i].time << " | " << v[i].d << " | " << v[i].low << endl;
    //   // cout << "distance of node " << i << " from " << start << " is " << v[i].value << endl;
    //
    // }
  }

  return 0;
}
