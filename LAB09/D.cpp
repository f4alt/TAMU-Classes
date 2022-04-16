#include <bits/stdc++.h>

using namespace std;

struct node {
  bool left = false;
  int incoming = 0;
  int neighborsleft = 0;
  vector<int> adj;
};

int main() {
  int c, p, x, l;

  cin >> c >> p >> x >> l;

  vector<node> v(c+1);

  for(int i = 0; i < p; i++) {
    int a, b;

    cin >> a >> b;

    v[a].incoming++;
    v[a].neighborsleft++;
    v[a].adj.push_back(b);

    v[b].incoming++;
    v[b].neighborsleft++;
    v[b].adj.push_back(a);
  }

  queue<int> q;

  v[l].left = true;

  for (int i=0; i < v[l].adj.size(); i++) {
    int pos = v[l].adj[i];
    q.push(pos);
    v[pos].neighborsleft--;
  }

  while (q.size() > 0) {
    int c = q.front();
    q.pop();

    if (v[c].left == true) {
      continue;
    }

    if (v[c].neighborsleft <= v[c].incoming / 2) {
      v[c].left = true;
      for (int i=0; i < v[c].adj.size(); i++) {
        int pos = v[c].adj[i];
        q.push(pos);
        v[pos].neighborsleft--;
      }
    }
  }

  if (v[x].left) {
    cout << "leave" << endl;
  }
  else {
    cout << "stay" << endl;
  }
}
