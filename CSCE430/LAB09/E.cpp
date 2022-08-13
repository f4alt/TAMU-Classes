#include <bits/stdc++.h>

using namespace std;

int parent[500000];

int dist(vector<pair<int, int>>& v, int i, int j) {
  return abs(v[i].first - v[j].first) + abs(v[i].second - v[j].second);
}

// initializes 0 to 'stop' in parent[] with itself
void initWithSelf(int stop) {
  for (int i=0; i <= stop; i++) {
    parent[i] = i;
  }
}

int find(int x) {
  if (parent[x] == x) {
    return x;
  }
  return parent[x] = find(parent[x]);
}

void merge(int a, int b) {
  int tempA = find(a);
  int tempB = find(b);
  if (tempA != tempB) {
    parent[tempB] = tempA;
  }
}

// prints parent[] from 0 to stop position
void printParents(int stop) {
  cout << "printing parent[] from 0 to " << stop << ":\n";
  for (int i=0; i <= stop; i++) {
    cout << parent[i] << " ";
  }
  cout << "\n\n";
}

int main() {
  int cases, n;

  cin >> cases;

  while (cases--) {
    cin >> n;
    n += 2;

    vector<pair<int, int> > inputs;
    for (int i=0; i < n; i++) {
      pair<int, int> temp;
      cin >> temp.first >> temp.second;
      inputs.push_back(temp);
    }


    initWithSelf(n);

    for (int i=0; i < n-1; i++) {
      for (int j=i; j < n; j++) {
        if (dist(inputs, i, j) <= 1000) {
          merge(i, j);
        }
      }
    }

    if (find(0) == find(n-1)) {
      cout << "happy" << endl;
    } else {
      cout << "sad" << endl;
    }
  }














  return 0;
}
