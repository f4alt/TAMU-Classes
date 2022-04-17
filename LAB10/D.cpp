#include <bits/stdc++.h>

using namespace std;

void split_input(vector<string>& ans, string& s) {
    ans.push_back("");

    for(auto i : s) {
        if(i == ' ') {
            ans.push_back("");
        }
        else {
            ans.back().push_back(i);
        }
    }

    // remove colon
    ans[0].pop_back();
}

int main() {
    int n;
    cin >> n;

    vector<string> rev;
    map<string,int> cnv;
    vector<vector<int>> adj(n);

    cin.ignore();
    for(int i = 0; i < n; i++)  {
        string s;
        getline(cin, s);

        vector<string> v;
        split_input(v, s);

        for(auto i : v) {
            if(cnv.count(i) == 0) {
                cnv[i] = rev.size();
                rev.push_back(i);
            }
        }

        int n1 = cnv[v[0]];
        for(int i = 1; i < v.size(); i++) {
            adj[cnv[v[i]]].push_back(n1);
        }
    }

    string start;
    cin >> start;
    int startidx = cnv[start];

    vector<int> deg(n,0);
    for(int i = 0; i < n; i++) {
        for(auto j : adj[i]) {
            deg[j]++;
        }
    }

    queue<int> zeroin;
    for(int i = 0; i < n; i++) {
        if(deg[i] == 0 && i != startidx) {
            zeroin.push(i);
        }
    }

    while(!zeroin.empty()) {
        int curr = zeroin.front();
        zeroin.pop();

        for(auto next : adj[curr]) {
            deg[next]--;
            if(deg[next] == 0 && next != startidx) {
                zeroin.push(next);
            }
        }
    }

    zeroin.push(startidx);
    while(!zeroin.empty()) {
        int curr = zeroin.front();
        zeroin.pop();
        cout << rev[curr] << endl;

        for(auto next : adj[curr]) {
            deg[next]--;
            if(deg[next] == 0) {
                zeroin.push(next);
            }
        }
    }

    return 0;
}
