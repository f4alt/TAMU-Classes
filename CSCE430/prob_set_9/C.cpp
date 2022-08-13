#include<bits/stdc++.h>

using namespace std;

struct Graph {
    int V, E;
    vector< pair<int, pair<int, int> > > edges;

    Graph(int V, int E) {
        this->V = V;
        this->E = E;
    }

    void addEdge(int u, int v, int w) {
        edges.push_back({w, {u, v}});
    }

    int kruskalMST();
};

struct DisjointSets {
    int *parent, *rnk;
    int n;

    DisjointSets(int n) {
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];

        for (int i = 0; i <= n; i++) {
            rnk[i] = 0;

            parent[i] = i;
        }
    }

    int find(int u) {
        if (u != parent[u]) {
          parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void merge(int x, int y) {
        x = find(x), y = find(y);

        if (rnk[x] > rnk[y]) {
          parent[y] = x;
        } else {
          parent[x] = y;
        }

        if (rnk[x] == rnk[y]) {
          rnk[y]++;
        }
    }
};

int Graph::kruskalMST() {
    int mst_wt = 0;

    sort(edges.begin(), edges.end());

    DisjointSets ds(V);

    vector< pair<int, pair<int, int> > >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++) {
        int u = it->second.first;
        int v = it->second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        if (set_u != set_v) {
            mst_wt += it->first;
            ds.merge(set_u, set_v);
        }
    }

    return mst_wt;
}

int main() {
  int num_tests, M, C, w, a, b;

  cin >> num_tests;

  while (num_tests--) {
    cin >> M >> C;
    Graph g(C, C*(C-1)/2);

    for (int i=0; i < C*(C-1)/2; i++) {
      cin >> w >> a >> b;
      g.addEdge(w, a, b);
    }

    int mst_wt = g.kruskalMST();
    mst_wt += C;

    if (mst_wt <= M) {
      cout << "yes" << endl;
    } else {
      cout << "no" << endl;
    }
  }

  return 0;
}
