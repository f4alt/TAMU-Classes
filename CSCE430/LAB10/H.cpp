#include <bits/stdc++.h>

using namespace std;

int parent[1000000];
int par_size[1000000];

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
  int n, q;
  char choice;

  cin >> n >> q;

  initWithSelf(n);


  while (q--) {
    cin >> choice;

    if (choice == 't') {
      int a, b;
      cin >> a >> b;
      merge(a, b);
    }

    if (choice == 's') {
      int a;
      cin >> a;
      cout << par_size[find(a)] << endl;
    }
  }









  return 0;
}
