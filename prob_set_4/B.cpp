#include <bits/stdc++.h>

using namespace std;

int main() {
  int test_cases, num_movies, num_moves, temp;

  cin >> test_cases;
  for (int z=0; z < test_cases; z++) {
    list<int> moviestack;
    cin >> num_movies >> num_moves;

    for (int i=0; i < num_movies; i++) {
      moviestack.push_back(i);
    }

    // for (auto i : moviestack) {
    //   cout << i << endl;
    // }
    // cout << endl;

    for (int i=0; i < num_moves; i++) {
      cin >> temp;

      int cnt = 0;
      for (auto i : moviestack) {
        if (i == temp-1) {
          // moviestack.remove(i);
          break;
        }
        cnt++;
      }

      moviestack.push_front(temp-1);

      cout << cnt << " ";

      // for (auto i : moviestack) {
      //   cout << i << endl;
      // }
      // cout << endl;
    }
    cout << endl;
  }

  return 0;
}
