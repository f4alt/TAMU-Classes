#include <bits/stdc++.h>

using namespace std;

int parent[200001];

int find(int x) {
  if (parent[x] == x) {
    return x;
  }
  return parent[x] = find(parent[x]);
}

bool merge(int a, int b) {
  int tempA = find(a);
  int tempB = find(b);
  if (tempA != tempB) {
    parent[tempB] = tempA;
    return true;
  }
  return false;
}

int main() {
  int individuals, loop2, temp, merges=0;
  bool possible = true;
  map<int, vector<int>> groups;
  map<int, vector<int>>::iterator it;
  // vector<char *> ans;
  string ans = "";

  // set parents to themselves and size 1
  for (int i=0; i < 200001; i++) {
    parent[i] = i;
    // size_w_par[i] = 1;
  }

  cin >> individuals;
  for (int i=0; i < individuals; i++) {
    cin >> loop2;

    for (int x=0; x<loop2; x++) {
      cin >> temp;
      groups[temp].push_back(i);
    }
  }

  for (it = groups.begin(); it != groups.end(); it++) {
    // cout << it->first << "* size:" << it->second.size() << endl;;
    for (int j=1; j < it->second.size(); j++) {
      // cout << it->second[j] + 1 << endl;
      // check if merge had to update parent
      if (merge(it->second[j], it->second[j-1])) {
        // cout << it->second[j-1] + 1 << " " << it->second[j] + 1 << " " << it->first << endl;
        char buf[100000];
        sprintf(buf, "%d %d %d\n", it->second[j-1] + 1, it->second[j] + 1, it->first);
        // cout << buf << endl;
        // ans.push_back(buf);
        // cout << ans[1] << endl;
        ans.append(buf);
        merges++;
      }

    }
    // cout << endl;
  }
  // cout << merges << endl;

  // // reset parents to themselves and size 1
  // for (int i=0; i < 200001; i++) {
  //   parent[i] = i;
  //   // size_w_par[i] = 1;
  // }

  // cout << ans[1] << endl << endl;

  if (merges != individuals - 1) {
    cout << "impossible" << endl;
  } else {
    cout << ans;
    // for (int i=0; i < merges; i++) {
    //   cout << i << endl;
    //   cout << ans[i] << endl;
    // }
    // for (it = groups.begin(); it != groups.end(); it++) {
    //   // cout << it->first << "* size:" << it->second.size() << endl;;
    //   for (int j=0; j < it->second.size(); j++) {
    //     // cout << it->second[j] + 1 << endl;
    //     // check if merge had to update parent
    //     if (merge(it->second[j], it->second[j-1])) {
    //       cout << it->second[j-1] + 1 << " " << it->second[j] + 1 << " " << it->first << endl;
    //       // merges++;
    //     }
    //
    //   }
    //   // cout << endl;
    // }
  }


  return 0;
}
