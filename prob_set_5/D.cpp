#include <bits/stdc++.h>

using namespace std;

int main() {
  int row_amt, col_amt, temp;
  priority_queue<int> rows;
  vector<int> cols;

  cin >> row_amt >> col_amt;

  // cols.resize(col_amt+1);

  while (row_amt--) {
    cin >> temp;
    rows.push(temp);
  }

  while (col_amt--) {
    cin >> temp;
    cols.push_back(temp);
  }
  // cols.push_back(0);

  sort(cols.begin(), cols.end(), greater<int>());


  while (!rows.empty()) {
    for (int i=0; i < rows.top(); i++) {
      // cout << "i:" << i << endl;
      // for (auto col : cols) {
      //   cout << col << " ";
      // }
      // cout << endl;

      if (cols[i] == 0) {
        cout << "No\n";
        return 0;
      }
      cols[i]--;
      // for (auto col : cols) {
      //   cout << col << " ";
      // }
      // cout << endl;
      // if (cols[i] == 0) {
        // cols.erase(cols.begin() + i);
      // }
    }
    sort(cols.begin(), cols.end(), greater<int>());
    rows.pop();
  }

  if (cols[0] == 0) {
    cout << "Yes\n";
  } else {
    cout << "No\n";
  }


















  return 0;
}
