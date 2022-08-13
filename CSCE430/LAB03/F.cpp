#include <bits/stdc++.h>

using namespace std;

int main() {
  int qnty;
  int temp;

  cin >> qnty;

  list<int> cards;

  for (int i=0; i < qnty; i++) {
    cin >> temp;

    if (!cards.empty() && (cards.back() + temp) % 2 == 0) {
      cards.pop_back();
    } else {
      cards.push_back(temp);
    }
  }

  // while(!carde.empty() && keep_going) {

  cout << cards.size() << endl;


  return 0;
}
