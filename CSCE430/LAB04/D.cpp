#include <bits/stdc++.h>

using namespace std;

int main() {
  long long moves, temp, blast_level=0, blasts=0;
  vector<long long> vec;

  cin >> moves;

  for (int i=0; i < moves; i++) {
    cin >> temp;
    vec.push_back(temp);
  }
  sort(vec.begin(), vec.end());

  blasts = moves;
  for (int i=0; i < moves; i++) {
    // cout << "blasts:" << blasts << " pos:" << moves - i - 1 << " vec[i]:" << vec[i] << endl;
    blasts = min(blasts, moves - i - 1 + vec[i]);
  }

  cout << blasts << endl;

}
