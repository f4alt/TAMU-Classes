#include <bits/stdc++.h>

using namespace std;

int main() {
  int N, max_L=-INT_MAX, max_R=-INT_MAX, max_ans=-INT_MAX, temp;

  cin >> N;
  int inputs[N];
  int max_L_arr[N];
  int max_R_arr[N];

  for (int i=0; i < N; i++) {
    cin >> temp;

    max_L = max(max_L, temp);
    max_L_arr[i] = max_L;

    // cout << max_L << " ";
    inputs[i] = temp;
  }
  // cout << endl;

  for (int i=N-1; i >= 0; i--) {
    // cout << inputs[i] << endl;
    max_R = max(inputs[i], max_R);
    max_R_arr[i] = max_R;

    // cout << max_R << " ";
  }
  // cout << endl;

  for (int i=0; i < N; i++) {
    int bridge_cal = min(max_R_arr[i], max_L_arr[i]) - inputs[i];
    max_ans = max(max_ans, bridge_cal);

    // cout << max_ans << " ";
  }

  // cout << endl;
  cout << max_ans << endl;
}
