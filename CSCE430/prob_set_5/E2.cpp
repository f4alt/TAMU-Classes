#include <bits/stdc++.h>

using namespace std;

bool customCmp (const pair<int, set<int>>& lhs, const pair<int, set<int>>& rhs) {
  return lhs.second.size() > rhs.second.size();
}

int main() {
  int enclosures, left, right;
  vector<pair<int, set<int>>> restrictions;
  vector<int> order;

  cin >> enclosures;
  restrictions.resize(enclosures+1);
  order.resize(enclosures+1, -1);

  for(int i=0; i < restrictions.size(); i++) {
    restrictions[i].first = i;
  }

  while(scanf("%d-%d\n", &left, &right) != EOF) {
    restrictions[left].second.insert(right);
    restrictions[right].second.insert(left);
  }

  std::sort(restrictions.begin()+1, restrictions.end(), customCmp);


  for (int i=1; i <= enclosures; i++) {
    set<int> cant_be;
    for (auto res : restrictions[i].second) {
        cant_be.insert(order[res]);
    }

    // TEST PRINT
    cout << i << " cant be: ";
    for (auto i : cant_be) {
      cout << i << " ";
    }
    cout << "\n";

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
      order[1] = 1;
      order[i] = rand() % 4 + 1;
      i = 2;
    }
  }

  // restriction print
  for (int i=1; i < restrictions.size(); i++) {
    cout << restrictions[i].first << ": ";
    for (auto it : restrictions[i].second) {
      cout << it << " ";
    }
    cout << endl;
  }
  cout << endl;

  // answer
  for (int i=1; i < order.size(); i++) {
    cout << i << " " << order[i] << "\n";
  }

  return 0;
}
