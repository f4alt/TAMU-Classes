#include <bits/stdc++.h>

using namespace std;

vector<int> vals;
vector<vector<long long>> mydp;

long long dp(int curr, int last_jump) {
    if (curr == vals.size() - 1) { // base case
      return vals[curr];
    }
    if (curr < 0 || curr >= vals.size()) { // out of bounds
      return LLONG_MAX;
    }

    if (mydp[last_jump][curr] < LLONG_MAX) { // memoize
      return mydp[last_jump][curr];
    }

    long long check_forward = dp(curr + last_jump + 1, last_jump + 1);
    long long check_backward = dp(curr - last_jump, last_jump);

    int ret = min(check_forward, check_backward) + vals[curr];
    mydp[last_jump][curr] = ret;
    return ret;
}

int main() {
    int squares, temp;
    cin >> squares;

    vals.resize(squares, 0);
    mydp.resize(squares+1, vector<long long>(squares+1, LLONG_MAX));

    for (int i=0; i < squares; i++) {
       // cin >> temp;
       // vals.push_back(temp);
       cin >> vals[i];
    }

    cout << dp(1, 1) << endl;





    return 0;
}
