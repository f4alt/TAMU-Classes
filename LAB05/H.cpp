#include <bits/stdc++.h>

using namespace std;

int parent[200001];

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
    // return true;
  }
  // return false;
}

int main() {
  int houses, queries, one, two;
  vector<set<int> > sets;

  cin >> houses >> queries;

  sets.resize(houses+1);

  for (int i=0; i < houses; i++) {
    // set<int> temp;
    // temp.insert(i+1);
    // sets[i+1] = temp;
    parent[i] = i;
  }

  while (queries--) {
    cin >> one >> two;

    // set<int> res;
    // std::set_union(sets[one].begin(), sets[one].end(),
    //             sets[two].begin(), sets[two].end(),
    //             std::inserter(res, res.begin()));
    // sets[one] = res;
    // sets[two] = res;
    //
    // if (sets[one].find(1) != sets[one].end() || sets[two].find(1) != sets[two].end() ) {
    //   sets[1] = res;
    // }
    //
    merge(one, two);

    // cout << "RES:";
    // for (auto it=res.begin(); it != res.end(); ++it) {
    //   cout << *it << " ";
    // }
    // cout << endl;
  }

  int incr = 1;
  bool bad = false;
  int last;
  // for (auto it=sets[1].begin(); it != sets[1].end(); ++it) {
  //   if (*it != incr) {
  //     cout << *it << "\n";
  //     bad = true;
  //   }
  //   last = *it;
  //   incr++;
  //   // cout << *it << " ";
  // }
  for (int i=1; i <= houses; i++) {
    if (parent[i] != 1) {
      bad = true;
      cout << i << "\n";
    }
  }
  // if (bad || last+1 < houses) {
  //   for (int i=last+1; i <= houses; i++) {
  //     cout << i << "\n";
  //   }
  // } else {
  //   cout << "Connected\n";
  // }
  if (!bad) {
    cout << "Connected\n";
  }
  // cout << endl;






  return 0;
}
