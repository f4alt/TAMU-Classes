#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    string str;

    cin >> n >> str;

    vector<pair<char, int> > moves;
    char prev = str[0];
    int cnt = 1;

    // successive moves
    for (int i = 1; i < str.size(); ++i) {
      if (str[i] == prev) {
        cnt++;
      } else {
        moves.push_back({prev, cnt});
        cnt = 1;
        prev = str[i];
      }
    }
    moves.push_back({prev, cnt});


    int next = 1;
    int output = 0;
    for (int j = 0; j < moves.size(); ++j) {
      pair<char, int> curr = moves[j];

      if (curr.first == 'L') {
        for (int i = next+curr.second; i >= next; --i) {
          cout << i << endl;
          output++;
        }

        next += curr.second + 1;
      } else {
        if (j > 0 && j+1 < moves.size()) {
          curr.second--;
        }

        for (int i = next, cnt = 0; cnt < curr.second; ++cnt, ++i) {
          cout << i << endl;
          output++;
        }
        next += curr.second;
      }

    }

    // cout << "output:" << output << endl;

    if (output != n) {
      cout << n << endl;
    }












    return 0;
}
