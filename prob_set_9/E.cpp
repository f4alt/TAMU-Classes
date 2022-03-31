#include <bits/stdc++.h>

using namespace std;

struct node {
  int value = -1;
  bool visited = false;
  vector<int> adj;
  vector<int> weight;
};

vector<node> v;
vector<long long> initial_stations;

long long BFS(int start) {
  priority_queue<pair<long long,int>,
                         vector<pair<long long,int>>,
                         greater<pair<long long,int>>> q;

   for (int i=0; i < initial_stations.size(); i++) {
      // cout << "station:" << initial_stations[i]+1 << endl << "pushing: " << endl;
      for (int j=0; j < v[initial_stations[i]].adj.size(); j++) {
            q.push({v[initial_stations[i]].weight[j], v[initial_stations[i]].adj[j]});
            // cout << v[initial_stations[i]].adj[j]+1 << " ";
        }
        // cout << endl;
    }

    long long total = 0;

    while(!q.empty()) {
        long long curr = q.top().second;
        long long dist = q.top().first;
        // cout << curr << " | " << dist << endl;
        q.pop();

        if(v[curr].visited) {
            continue;
        }
        v[curr].visited = true;

        total += dist;

        for (int i=0; i < v[curr].adj.size(); i++) {
        // for(auto i : v[curr].adj) {
          // cout << "pushing:" << v[curr].adj[i] << endl;
            q.push({v[curr].weight[i], v[curr].adj[i]});
        }
    }

    return total;
}

int main() {
  long long num_datasets, N, M, L, S, stati, statj, statEij;

  cin >> num_datasets;

  while (num_datasets--) {
    cin >> N >> M >> L >> S;

    v.clear();
    initial_stations.clear();
    // node def_node;
    // def_node.adj.resize(N+1);
    // def_node.weight.resize(N+1);
    v.resize(N);
    initial_stations.resize(S);

    // take in starting stations
    for (int i=0; i < S; i++) {
      cin >> stati;
      stati--;

      v[stati].visited = true;
      initial_stations[i] = stati;
      // initial_stations.push_back(stati);
    }

    // create graph
    for (int i=0; i < M; i++) {
      cin >> stati >> statj >> statEij;
      stati--;
      statj--;

      v[stati].adj.push_back(statj);
      v[stati].weight.push_back(statEij+L);

      v[statj].adj.push_back(stati);
      v[statj].weight.push_back(statEij+L);
    }

    // for (int i=0; i < v.size(); i++) {
    //   cout << "v:" << i+1 << endl;
    //   for (int j=0; j < v[i].adj.size(); j++) {
    //     cout << v[i].adj[j]+1 << " ";
    //   }
    //   cout << endl;
    // }
    // cout << endl;

    // int total = 0;
    // for (int i=0; i < S; i++) {
    //   total += BFS(initial_stations[i]);
    // }

    // cout << total << endl;

    cout << BFS(0) << endl;

  }






  return 0;
}
