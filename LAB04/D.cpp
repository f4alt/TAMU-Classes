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

  for (int i=0; i < vec.size()-1; i++) {
    // cout << vec[i] << " | " << vec[i+1] << " / " << vec[i] - blast_level << endl;
    if (vec[i] == vec[i+1] && vec[i] - blast_level < vec.size() - i) {
      // cout << "horizontal for:" << vec[i] - blast_level << endl;
      blasts += vec[i] - blast_level;
      blast_level += vec[i] - blast_level;
    }
  }

  // cout << endl;
  for (int i=0; i < vec.size(); i++) {
    // cout << vec[i] << " | " << blast_level << endl;
    if (vec[i] > blast_level) {
      // cout << "vertical for:" << vec.size() - i << endl;
      blasts += vec.size() - i;
      break;
    }
  }

  cout << blasts << endl;

}
