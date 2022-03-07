#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> cant_be;
vector<int> type;


void solve(int pos) {
    if (pos == type.size()) { // end
        for(int i = 0; i < type.size(); ++i) {
            cout << i+1 << ' ' << type[i] << '\n';
        }
        exit(0);
    }
    for(int assignment = 1; assignment <= 4; assignment++) {
        bool good = true;
        for(const int &to : cant_be[pos]) {
            if(to >= pos) {
              break;
            }
            if(type[to] == assignment) {
                good = false;
                break;
            }
        }
        if (good) {
            type[pos] = assignment;
            solve(pos+1);
        }
    }
}

int main() {
    int n;
    cin >> n;

    cant_be.resize(n);
    type.resize(n);

    int left, right;
    char dash;
    cin >> left >> dash >> right;
    while(!cin.eof()) {
        left--;
        right--;
        cant_be[left].push_back(right);
        cant_be[right].push_back(left);

        cin >> left >> dash >> right;
    }
    for(int i = 0; i < n; ++i) {
        sort(cant_be[i].begin(), cant_be[i].end());
        cant_be[i].erase(unique(cant_be[i].begin(), cant_be[i].end()), cant_be[i].end());
    }
    solve(0);
}
