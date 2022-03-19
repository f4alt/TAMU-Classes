#include <bits/stdc++.h>

using namespace std;

int num_wagons, wagons_rem, num_loco;
int pos[10001];

bool possible(int a) {
    int l = 0, r = a-1;
    int i = 0;
    int count = 0;

    while (l <= r) {
        count++;

        if (i == wagons_rem) {
          break;
        }

        if (pos[i] > r) {
          l = pos[i];
        } else {
          while(i < wagons_rem) {
            if (pos[i] > r) {
              break;
            }
            i++;
          }
          l = r+1;
        }
        r = min(l + a-1, num_wagons-1);
        // cout << "r:" << r << " | " << i << endl;
    }

    if (count <= num_loco) {
      return true;
    }
    return false;
}

int main() {
    int test_cases;

    cin >> test_cases;

    while (test_cases--) {
        cin >> num_wagons >> wagons_rem >> num_loco;

        for (int i=0; i < wagons_rem; i++) {
          cin >> pos[i];
          pos[i]--;
        }

        int l = 1, r = num_wagons;

        while (l < r) {
            int a = (l + r) >> 1;
            if (possible(a)) {
                r = a;
            } else {
                l = a + 1;
            }
        }

        cout << l << endl;
    }


    return 0;
}
