#include <bits/stdc++.h>

using namespace std;


struct node {
  int value = -1;
  int deg = 0;
  vector<int> adj;
  vector<int> weight;
};

unordered_map<string, pair<int, vector<string>>> speaks;
unordered_map<string, pair<int, vector<string>>> understands;
vector<node> v;
unordered_set<string> vis;


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


void dfs1(stack<string>& r, string curr) {
    if (vis.count(curr) > 0) {
        return;
    }

    vis.insert(curr);

    for(auto next : speaks[curr].second) {
        dfs1(r, next);
    }

    r.push(curr);
}

void dfs2(vector<string>& comp, string curr) {
    if (vis.count(curr) > 0) {
      return;
    }
    
    vis.insert(curr);
    comp.push_back(curr);

    for (auto next : understands[curr].second) {
      dfs2(comp, next);
    }
}

int main() {
    int n;
    cin >> n;

    unordered_set<string> names;

    for(int i = 0; i < n; i++) {
      string name, speak, understand;
      cin >> name >> speak;

      names.insert(speak);

      speaks[speak].first++;
      understands[speak].first++;

      // cout << speak << " | ";
      while((cin.peek() != '\n') && (cin >> understand)) {
        // cout << understand << endl;
        speaks[speak].second.push_back(understand);
        understands[understand].second.push_back(speak);
      }
    }

    // for (auto i : speaks) {
    //   cout << "forward: " << i.first << endl;
    //   for (auto j : i.second.first) {
    //     // cout << j.first << " | " << j.second << endl;
    //   }
    // }

    stack<string> r;

    for(auto i : names) {
      if (vis.count(i) > 0) {
        continue;
      }

      dfs1(r, i);
    }

    vis.clear();


    int best = 0;

    while(!r.empty()) {
      string curr = r.top();
      r.pop();

      if (vis.count(curr) > 0) {
        continue;
      }

      vector<string> comp;
      dfs2(comp, curr);

      int check = 0;

      for(auto i : comp) {
        check += speaks[i].first;
      }

      best = max(check, best);
    }

    cout << n - best << endl;
}
