#include <math.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// H

int main() {
    long long t, x, y;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> x >> y;
        string status;

        if (y == 0) {
            cout << "Case #" << i + 1 << ": " << "OFF" << endl;
            continue;
        }

        long long z = pow(2, x - 1);
        if ((y+1) % (z*2) == 0) {
            status = "ON";
        } else {
            status = "OFF";
        }

        cout << "Case #" << i + 1 << ": " << status << endl;
    }
}
