#include <bits/stdc++.h>

using namespace std;

int main() {
  int numbers, instructions, type, p, q;
  vector<set<int>> sets;
  vector<int> sets_sum;

  cin >> numbers >> instructions;

  // initialize each index to set with itself
  for (int i=0; i < numbers; i++) {
    set<int> temp = {i+1};
    sets.push_back(temp);
    sets_sum.push_back(i+1);
  }

  for (int z=0; z < instructions; z++) {
    cin >> type;

    if (type == 1) {
      // union
      cin >> p >> q;

      set<int> result;
      int sum = sets_sum[p-1] + sets_sum[q-1];
      set_union(sets[p-1].begin(), sets[p-1].end(), sets[q-1].begin(), sets[q-1].end(), inserter(result, result.begin()));
      // for (auto i : result) {
      //   cout << i << endl;
      // }
      for (auto i : result) {
        sets[i-1] = result;
        sets_sum[i-1] = sum;
      }
    }
    if (type == 2) {
      // move
      cin >> p >> q;

      for (int i=0; i < sets.size(); i++) {
        set<int>::iterator it = sets[i].find(p);
        if (it != sets[i].end()) {
          sets[i].erase(it);
        }
      }

      sets[q-1].insert(p);
      int sum = sets_sum[q-1] + p;
      for (auto i : sets[q-1]) {
        sets[i-1] = sets[q-1];
        sets_sum[i-1] = sum;
      }

      sets_sum[p-1] -= p;
    }
    if (type == 3) {
      // output
      cin >> p;

      cout << sets[p-1].size() << " " << sets_sum[p-1] << endl;
    }

    for (int i=0; i < sets.size(); i++) {
      cout << i+1 << ":";
      for (auto it : sets[i]) {
        cout << it << " ";
      }
      cout << "| " << sets_sum[i] << endl;
    }
    cout << endl;
  }

  return 0;
}
