#include <bits/stdc++.h>

using namespace std;

int main() {
  int enclosures, left, right;
  vector<set<int>> restrictions;
  vector<int> order;

  cin >> enclosures;
  restrictions.resize(enclosures+1);
  order.resize(enclosures+1, -1);

  while(scanf("%d-%d\n", &left, &right) != EOF) {
    restrictions[left].insert(right);
    restrictions[right].insert(left);
  }

  // first should always be 1
  order[1] = 1;
  int stuck_try = 2;

  for (int i=2; i <= enclosures; i++) {
    set<int> cant_be;
    for (auto res : restrictions[i]) {
      // if (res >= i) {
      //   break;
      // } else {
        cant_be.insert(order[res]);
      // }
    }

    // TEST PRINT
    // cout << i << " cant be: ";
    // for (auto i : cant_be) {
    //   cout << i << " ";
    // }
    // cout << "\n";

    set<int>::iterator it = cant_be.begin();
    bool assigned = false;
    if (*it == -1) {
      it++;
    }
    for (int j=1; j <= 4; j++) {
      if (cant_be.empty() || it == cant_be.end() || *it != j) {
        order[i] = j;
        assigned = true;
        break;
      }
      it++;
    }
    if (!assigned) {
      // order.resize(enclosures+1, -1);
      order[1] = 1;
      order[i] = rand() % 4 + 1;
      i = 2;
    }
  }
  // TEST PRINT
  // cout << endl;

  // TEST PRINT
  for (int i=1; i < restrictions.size(); i++) {
    cout << i << ": ";
    for (auto it : restrictions[i]) {
      cout << it << " ";
    }
    cout << endl;
  }
  cout << endl;


  // answer
  for (int i=1; i < order.size(); i++) {
    cout << i << " " << order[i] << "\n";
    if (order[i] == -1) {
      return -1;
    }
  }

  return 0;
}
