#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// B

struct node {
    int value = -1;
    vector<int> adj;
};
vector<node> v;

int BFS(int start) {
    int output = 0;
    int a, b;

    if (v[start].value != -1) return output;

    // init node 1 as distance 0
    v[start].value = 0;

    // using queue
    queue<int> q;
    q.push(start);
    output++;

    // optional 'time' to keep track of order we encounter each node
    // int time = 0;
    while (!q.empty()) {
        a = q.front();
        q.pop();
        // time++;
        // cout << "encountered node " << a << " at time " << time << endl;
        for (int i = 0; i < v[a].adj.size(); i++) {
            b = v[a].adj[i];
            if (v[b].value == -1) {  // if not visited yet
                v[b].value =
                    v[a].value + 1;  // distance is one away from current
                q.push(b);
                output++;
            }
        }
    }

    return output;
}

int main() {
    int t, n, m, l, x, y;
    cin >> t;
    while (t--) {
        cin >> n >> m >> l;
        node temp;
        v.clear();
        v.resize(n + 1, temp);
        for (int i = 0; i < m; i++) {
            cin >> x >> y;
            v[x].adj.push_back(y);
        }

        int output = 0;
        for (int i = 0; i < l; i++) {
            cin >> x;
            output += BFS(x);
        }

        cout << output << endl;
    }
}
