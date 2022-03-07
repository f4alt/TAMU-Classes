#include <bits/stdc++.h>

using namespace std;

int main() {
  int num_balloons, max=0, curr, arrows=0;
  multiset<int> poppable;

  cin >> num_balloons;

  while (num_balloons--) {
    cin >> curr;

    // for (auto i : poppable) {
    //   cout << i << " ";
    // }
    // cout << endl;

    if (poppable.find(curr) != poppable.end()) {
      poppable.insert(curr-1);
      poppable.erase(poppable.find(curr));
      continue;
    }

    // cout << endl;
    // for (auto i : poppable) {
    //   cout << i << " ";
    // }
    // cout << endl;


    poppable.insert(curr-1);
    arrows++;
  }

  cout << arrows << endl;

  return 0;
}
