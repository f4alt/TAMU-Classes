#include <bits/stdc++.h>

using namespace std;

vector<int> prefix;
int n;
int cost;
int stop = 0;

int main() {
  int temp;

  cin >> n;

  prefix.resize(n+1, 0);

  for (int i=0; i < n; i++) {
    cin >> prefix[i];
  }

  int ans = 0;
  temp =0;
  int maxLen = 0;
  int len = 0;
  for (int j=0; j < n; j++) {
    if (temp + prefix[j] > 0) {
      len++;
      temp += prefix[j];
    }
    // temp = max(temp + prefix[j], 0);
    if (ans < temp) {
      ans = temp;
      maxLen = max(len, maxLen);
    }
    // ans = max(ans, temp);
  }

  cout << "len:" << maxLen << endl;
  cout << ans << endl;










  return 0;
}
