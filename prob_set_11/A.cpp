#include <bits/stdc++.h>

using namespace std;

struct node {
  int a;
  int b;
  int cap;
  int d;
};

// BFS (usuainty for shortest path)
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

int n, s, t, d[1000000], ptr[1000000], q[1000000];
vector<node> e;
vector<int> g[1000000];

void addedge(int a, int b, int cap) {
  node edge1, edge2;

  edge1 = { a, b, cap, 0 };
	edge2 = { b, a, 0, 0 };


  g[a].push_back(e.size());
	e.push_back(edge1);
	g[b].push_back(e.size());
	e.push_back(edge2);
}

bool bfs() {
	int qh=0, qt=0;
	q[qt++] = s;
	memset(d, -1, n * sizeof d[0]);
	d[s] = 0;
	while(qh < qt && d[t] == -1) {
		int v = q[qh++];
		for(size_t i=0; i<g[v].size(); ++i) {
			int id = g[v][i],
				to = e[id].b;
			if(d[to] == -1 && e[id].d < e[id].cap) {
				q[qt++] = to;
				d[to] = d[v] + 1;
			}
		}
	}
	return d[t] != -1;
}

int dfs(int v, int flow) {
	if (flow == 0) {
    return 0;
  }

	if (v == t){
    return flow;
  }

	for(; ptr[v]<(int)g[v].size(); ++ptr[v]) {
		int id = g[v][ptr[v]];
        int to = e[id].b;
		if(d[to] != d[v] + 1)  continue;
		int pushed = dfs(to, min (flow, e[id].cap - e[id].d));
		if(pushed) {
			e[id].d += pushed;
			e[id^1].d -= pushed;
			return pushed;
		}
	}
	return 0;
}

int getflow() {
	int flow = 0;
	for(;;) {
		if (!bfs()) {
      break;
    }

		memset(ptr, 0, n * sizeof ptr[0]);
		while(int pushed = dfs(s,1000000)) {
			flow += pushed;
    }
	}


	return flow;
}

int main() {
    int num_cases;
    cin >> num_cases;
    while(num_cases--) {
      int locations, start, group, time;
      cin >> locations >> start >> group >> time;
      start--;
      time++;

      int ends;
      cin >> ends;
      vector<int> locations_vec(ends);

      for(auto& i : locations_vec) {
        cin >> i;
        i--;
      }

      int r;
      cin >> r;
      vector<node> roads(r);
      for(auto& i : roads) {
        cin >> i.a >> i.b >> i.cap >> i.d;
        i.a--;
        i.b--;
      }

      n = locations * time + 2;
      s = n-1;
      t = n-2;

      addedge(s,start,group);

      for(int i = 1; i < time; i++) {
          int t1 = (i-1) * locations;
          int t2 = i * locations;
          for(int j = 0; j < locations; j++) {
              addedge(t1+j,t2+j,1000000);
          }
      }

      for(auto& i : roads) {
          for(int j = 0; j < time; j++) {
              if(j + i.d >= time) break;
              int t1 = j;
              int t2 = j + i.d;
              int n1 = t1*locations + i.a;
              int n2 = t2*locations + i.b;
              addedge(n1,n2,i.cap);
          }
      }

      for(auto i : locations_vec) {
          for(int j = 0; j < time; j++) {
              int n1 = j * locations + i;
              addedge(n1, ::t, 1000000);
          }
      }

      int ans = getflow();

      cout << ans << endl;

      e.clear();
      for(int i = 0; i < n; i++) {
          g[i].clear();
      }
      ans = 0;
    }











    return 0;
}
