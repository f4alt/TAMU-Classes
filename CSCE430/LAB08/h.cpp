#include <bits/stdc++.h>

using namespace std;

int parent[500000];
int par_size[500000];

// initializes 0 to 'stop' in parent[] with itself
void initWithSelf(int stop) {
  for (int i=0; i <= stop; i++) {
    parent[i] = i;
    par_size[i] = 1;
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
    par_size[tempB] += par_size[tempA];
    par_size[tempA] = par_size[tempB];
  }
}

// prints parent[] from 0 to stop position
void printParents(int stop) {
  cout << "printing parent[] from 0 to " << stop << ":\n";
  for (int i=0; i <= stop; i++) {
    cout << parent[i] << " | size: " << par_size[i] << endl;
  }
  cout << "\n\n";
}

int main() {
  int n, k, a, b, w;
  string left, right;

  // number of nodes
  cin >> n;

  for (int z=0; z < n; z++) {
    map<int, string> reverse;
    map<string, int> forward;
    int assignment = 0;
    // vector<set<int> > v;

    // number of connections
    cin >> k;

    memset(parent, -1, sizeof(parent));
    memset(par_size, -1, sizeof(par_size));
    initWithSelf(k+1);


      for (int i=0; i < k; i++) {
        // in form of "leftNode rightNode weight"
        cin >> left >> right;
        int aa, bb;
        if (forward.count(left) != 0) {
          aa = forward[left];
        } else {
          forward[left] = assignment;
          aa = assignment;
          assignment+=1;
          // cout << "assignment:" << assignment << endl;
        }

        if (forward.count(right) != 0) {
          bb = forward[right];
        } else {
          forward[right] = assignment;
          bb = assignment;
          assignment+=1;
          // cout << "assignment:" << assignment << endl;
        }

        // cout << left << " | " << aa << endl;
        // cout << right << " | " << bb << endl;

        aa+=1, bb+=1;

        merge(aa, bb);

        // printParents(5);

        cout << par_size[find(aa)] << endl;
      }
    }

  return 0;
}
