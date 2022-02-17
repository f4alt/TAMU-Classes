#include <bits/stdc++.h>

using namespace std;

int parent[1500000];
// count , sum
pair<long long, long long> info[1500000];

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
    info[tempA].first++;
    info[tempA].second += b;
  }
}

int main() {
  int numbers, instructions, type, p, q, temp;

  cin >> numbers >> instructions;

  // initialize each index to set with itself
  while (!cin.eof()) {
    for (int i=1; i <= numbers; i++) {
      parent[i] = i;
      parent[i+800000] = i+800000;
      merge(i+800000, i);
      info[i+800000] = { 1, i };
    }

    for (int z=0; z < instructions; z++) {
      cin >> type;

      if (type == 1) {
        // union
        cin >> p >> q;

        merge(p, q);
      }
      if (type == 2) {
        // move
        cin >> p >> q;

        info[find(p)].first--;
        info[find(p)].second -= p;
        parent[p] = find(q);
        info[find(q)].first++;
        info[find(q)].second += p;
      }
      if (type == 3) {
        // output
        cin >> p;


        cout << info[find(p)].first << " " << info[find(p)].second << endl;
      }
      // for (int i=1; i <= numbers; i++) {
      //   cout << i << " | " << find(i) << " | " << info[find(i)].first << "," <<info[find(i)].second << endl;
      // }
    }
    cin >> numbers >> instructions;
  }

  return 0;
}
