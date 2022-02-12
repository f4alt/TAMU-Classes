#include <bits/stdc++.h>

using namespace std;

int parent[500001], size_w_par[500001]={1};

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
    size_w_par[tempA] += size_w_par[tempB];
  }
}

int main() {
  int loop, ingred, temp, mixed_ingred, ans=0;
  set<int>::iterator it;

  // set parents to themselves and size 1
  for (int i=0; i < 500001; i++) {
    parent[i] = i;
    size_w_par[i] = 1;
  }

  cin >> loop;
  for (int z=0; z < loop; z++) {
    set<int> ingred_set; // reset
    cin >> ingred;
    for (int x=0; x < ingred; x++) {
      cin >> temp;
      // cout << "here" << endl;
      ingred_set.insert(find(temp));
    }
    // for (it = ingred_set.begin(); it != ingred_set.end(); it++) {
    //   cout << "set:" << *it << endl;
    // }
    mixed_ingred = 0;
    for (it = ingred_set.begin(); it != ingred_set.end(); it++) {
      mixed_ingred += size_w_par[*it];
      // cout << "mixed_ingred:" << mixed_ingred << " | " << *it << endl;
    }
    if (mixed_ingred == ingred) {
      // cout << "here2" << endl;
      ans++;
      for (it = ingred_set.begin(); it != ingred_set.end(); it++) {
        merge(*ingred_set.begin(), *it);
      }
    }
  }

  cout << ans << endl;


  return 0;
}
