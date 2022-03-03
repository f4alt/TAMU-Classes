#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

// B

int main() {
    int t, n, x, next, output;
    t = n = x = 0;

    cin >> t;
    for (int h = 0; h < t; h++) {
        cin >> n;
        next = 1;
        output = 0;
        for (int i = 0; i < n; i++) {
            cin >> x;
            if (x != next) {
                output++;
            } else {
                next = x+1;
            }
        }

        cout << output << endl;
    }
}
