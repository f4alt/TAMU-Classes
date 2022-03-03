#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <utility>
#include <algorithm>
#include <set>

using namespace std;

// D

int main() {
    int n, x, y;
    string command = "";
    map<int, priority_queue<int>> m;
    map<int, priority_queue<int>>::iterator it;
    long long gold = 0;

    cin >> n;
    for (int i = 0 ; i < n; i++) {
        cin >> command;
        if (command == "add") {
            cin >> x >> y;

            m[x].push(y);

            // for (auto i : m) {
            //   cout << i.first << " | " << i.second.size() << endl;
            // }
        } else {
            cin >> x;
            gold = 0;

            it = m.end();
            while (!m.empty()) {
      				it = m.lower_bound(x);

      				if (it == m.end()) {
                it--;
              }

      				while (it->first > x && it != m.begin()) {
      					it--;
      				}

      				if (it->first > x) {
                break;
              }

      				gold += it->second.top();
      				x -= it->first;
      				it->second.pop();

      				if (it->second.empty()) {
      					m.erase(it);
      				}
      			}

            cout << gold << endl;
        }
    }

}
