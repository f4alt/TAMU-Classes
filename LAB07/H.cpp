#include <bits/stdc++.h>

using namespace std;

long long find(vector<long long>& disjoint, long long a) {
    if(disjoint[a] == -1) {
        return a;
    }

    long long ret = find(disjoint, disjoint[a]);
    disjoint[a] = ret;
    return ret;
}

void join(vector<long long>& disjoint, long long a, long long b) {
    a = find(disjoint, a);
    b = find(disjoint, b);

    if (a == b) {
      return;
    }

    disjoint[b] = a;
}

int main() {
    long long num_friends, rem_friendships;
    cin >> num_friends >> rem_friendships;

    vector<long long> disjoint(num_friends, -1);
    vector<long long> debts(num_friends, 0);
    vector<long long> grouptotal(num_friends, 0);

    for(long long i = 0; i < num_friends; i++) {
        cin >> debts[i];
    }

    long long friend1, friend2;
    for(long long i = 0; i < rem_friendships; i++) {
        cin >> friend1 >> friend2;
        join(disjoint, friend1, friend2);
    }

    for(long long i = 0; i < num_friends; i++) {
        grouptotal[find(disjoint, i)] += debts[i];
    }

    for(auto i : grouptotal) {
        if (i != 0) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }
    cout << "POSSIBLE" << endl;
}
