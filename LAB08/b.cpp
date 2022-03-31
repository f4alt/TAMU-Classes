#include <bits/stdc++.h>

using namespace std;

struct runner {
    string name;
    double first;
    double second;
};

bool cmp_seconds(runner lhs, runner rhs) {
    return lhs.second < rhs.second;
}

pair<string, double> calc(vector<runner> v, int first) {
    string ans = v[first].name;
    ans.append("\n");

    double total = v[first].first;

    v.erase(v.begin()+first);

    sort(v.begin(), v.end(), cmp_seconds);

    total += v[0].second;
    total += v[1].second;
    total += v[2].second;

    ans.append(v[0].name);
    ans.append("\n");
    ans.append(v[1].name);
    ans.append("\n");
    ans.append(v[2].name);
    ans.append("\n");

    return {ans, total};
}

int main() {
    int n;
    cin >> n;

    vector<runner> runners(n);

    for(int i=0; i < n; i++) {
        cin >> runners[i].name >> runners[i].first >> runners[i].second;
    }

    double best = 1000000.0;
    string team;
    for (int i=0; i < n; i++) {
        pair<string, double> curr = calc(runners, i);
        if (curr.second < best) {
            best = curr.second;
            team = curr.first;
        }
    }

    cout << best << endl;
    cout << team;













    return 0;
}
