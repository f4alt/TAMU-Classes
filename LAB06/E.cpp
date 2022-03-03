#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <utility>
#include <algorithm>

using namespace std;

// E

int main() {
    long n, a;
    n = a = 0;
    stack<long> s;

    cin >> n;
    for (long i = 0; i < n*2; i++) {
        cin >> a;
        if (s.empty()) {
            s.push(a);
        } else if (s.top() == a) {
            s.pop();
        } else {
            s.push(a);
        }
    }
    
    if (s.empty()) {
        cout << 2*n;
    } else {
        cout << "impossible";
    }
}
