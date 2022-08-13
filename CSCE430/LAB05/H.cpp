#include <bits/stdc++.h>

using namespace std;

int parent[500000];

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
    if (tempB == 1) {
      parent[tempA] = tempB;
    } else {
      parent[tempB] = tempA;
    }
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
  int houses, queries, one, two;

  cin >> houses >> queries;

  initWithSelf(houses);

  while (queries--) {
    cin >> one >> two;

    merge(one, two);
  }

  bool bad = false;
  int last;
  for (int i=1; i <= houses; i++) {
    if (find(i) != 1) {
      bad = true;
      cout << i << "\n";
    }
  }
  if (!bad) {
    cout << "Connected\n";
  }





  return 0;
}
