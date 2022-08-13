#include <bits/stdc++.h>

using namespace std;

int main() {
  vector<long long> joe_need;
  vector<long long> sizes;
  long long wasted =0;
  long long offered, colors;
  long long temp;
  int j=0;

  cin >> offered >> colors;

  for (int i=0; i < offered; i++) {
    cin >> temp;

    sizes.push_back(temp);
  }
  for (int i=0; i < colors; i++) {
    cin >> temp;

    joe_need.push_back(temp);
  }

  sort(sizes.begin(), sizes.end());
  sort(joe_need.begin(), joe_need.end());

  for (int i=0; i < joe_need.size(); i++) {
    j = 0;

    while(1) {
      if (joe_need[i] <= sizes[j]) {
        wasted += sizes[j] - joe_need[i];
        break;
      } else {
        j++;
      }
    }
  }

  cout << wasted << endl;




}
