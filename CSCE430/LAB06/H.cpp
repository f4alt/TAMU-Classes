#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>

using namespace std;

// H

int LSOne(const int x) {
    return x & (-x);
}

class ft {
    vector<long long> a;
    int n;

    public:
    ft(int x) {
        n = x + 1;
        a.resize(n, 0);
    }

    int size() {
        return n;
    }

    long long at(int elem) {
        return rsq(elem, elem);
    }

    void increment(int elem, long long val) {
        while (elem <= n) {
            // cout << "tree[" << elem << "] += " << val << endl;
            a[elem] += val;
            elem = elem + LSOne(elem);
        }
        // this->print();
    }

    long long rsq(int elem) {
        long long sum = 0;
        while (elem > 0) {
            // cout << "sum += " << a[elem] << " from elem: " << elem << endl;
            sum += a[elem];
            elem -= LSOne(elem);
        }
        return sum;
    }

    long long rsq(int l, int r) {
        return rsq(r) - rsq(l-1);
    }

    void push1all() {
        for (int i = 1; i < n; i++) {
            increment(i, 1);
        }
    }

    void print() {
        for (int i = 1; i <= n; i++) {
            cout << rsq(i,i) << " ";
        }
        cout << endl;
    }
    void flip(int elem) {
      int add = 1;
      if (rsq(elem, elem) == 1) {
        add = -1;
      }
      while (elem <= n) {
        a[elem] += add;
        elem = elem + LSOne(elem);
      }
    }
};

int main() {
    int n = 0;
    int val = 0;
    map<int, int> m;

    cin >> n;
    ft tree (3*n);
    for (int i = 1; i <= n; i++) {
        cin >> val;
        tree.increment(i+n, 1);
        m.emplace(val, i+n);
    }

    // for (auto i : m) {
    //   cout << i.first << " | " << i.second << endl;
    // }

    // calc and move
    // tree.print();
    int end = n;
    int beginning = 1;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1) {
            // smaller number
            // x = i;
            // cout << "from " << i-i/2 << " to " << m[beginning] << endl;
            tree.flip(m[beginning]);
            cout << tree.rsq(i, m[beginning]) << endl;
            tree.flip(i);
            beginning++;
            // tree.increment(m[i], -1);
            // tree.increment(i, 1);
        } else {
            // x = n-i+2;
            // larger number
            // cout << "from " << m[end] << " to " << 3*n-i+1 << endl;
            // tree.increment(m[i], -1);
            // tree.increment(3*n-i+2, 1);
            tree.flip(m[end]);
            cout << tree.rsq(m[end], 3*n-i+1) << endl;
            tree.flip(3*n-i+1);
            end--;
        }
        // tree.print();
    }
}
