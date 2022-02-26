#include <bits/stdc++.h>

using namespace std;

int main() {
  int enclosures, left, right;
  vector<set<int>> restrictions;
  vector<int> order;

  scanf("%d\n", &enclosures);
  restrictions.resize(enclosures+1);
  order.resize(enclosures+1, -1);

  while(scanf("%d-%d\n", &left, &right) != EOF) {
    restrictions[left].insert(right);
    restrictions[right].insert(left);
  }

  for (int i=1; i < order.size(); i++) {
    if (order[i] == -1) {
    for (int cnt=0; cnt < 4; cnt++) {
        // order[i] = cnt;
        for (int j=1; j <= enclosures; j++) {
          cout << "restrictions[" << i << "] looking for " << j << endl;
          if (restrictions[i].find(j) == restrictions[i].end()) {
            cout << "here" << endl;
            order[j] = i;
            cout << "order[" << j << "] = " << i << endl;
          }
        }
        cout << "HERE " << cnt << " | " << i << endl;
        break;
      }
    }
  }

  for (int i=1; i < restrictions.size(); i++) {
    for (auto it : restrictions[i]) {
      cout << it << " ";
    }
    cout << endl;
  }
  cout << endl;
  for (int i=1; i < order.size(); i++) {
    cout << order[i] << " ";
  }
  cout << endl;





  return 0;
}
