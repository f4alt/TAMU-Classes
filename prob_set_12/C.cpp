#include <bits/stdc++.h>

using namespace std;

vector<int> scores = {0,0,0,1,1,2,3,5,11};
vector<vector<bool>> used(4, vector<bool>(4, false));

bool search(vector<vector<char>>& v, string& s, int i, int j, int ch) {
    if(ch == s.size()) {
        return true;
    }

    if(i < 0 || j < 0 || i == 4 || j == 4 || used[i][j] || v[i][j] != s[ch]) {
        return false;
    }

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {

            used[i][j] = true;
            bool good = search(v, s, i+x, j+y, ch+1);
            used[i][j] = false;

            if(good) return true;
        }
    }

    return false;
}

bool find(vector<vector<char>>& v, string& s) {
    for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 4; j++) {
        if (search(v, s, i, j, 0)) {
          return true;
        }
      }
    }
    return false;
}

int main() {
    int n;
    cin >> n;

    vector<string> dictionary(n);

    for (int i=0; i < n; i++) {
      cin >> dictionary[i];
    }

    int b;
    cin >> b;

    while (b--) {
      vector<vector<char>> curr_board;
      curr_board.resize(4, vector<char>(4));

      for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
          cin >> curr_board[i][j];
        }
      }

      int score = 0;
      string longest = "";
      int found = 0;

      for (int i=0; i < n; i++) {
        if (find(curr_board, dictionary[i])) {
          found++;
          if (dictionary[i].length() > longest.length()) {
            longest = dictionary[i];
          }
          if (dictionary[i].length() == longest.length() && dictionary[i] < longest) {
            longest = dictionary[i];
          }
          score += scores[dictionary[i].length()];
        }
      }

      cout << score << " " << longest << " " << found << endl;
    }
}
