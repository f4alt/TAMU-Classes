#include <bits/stdc++.h>

using namespace std;

int main() {
  int qnty;
  vector<pair<int, int>> choices;
  // std::map<int, int> choices;
  int temp;
  int round = 0;
  int eliminated;

  cin >> qnty;

  for (int i=0; i < qnty; i++) {
    cin >> temp;

    choices.push_back(make_pair(i, temp));
    // eliminated.push_back(i, temp);
  }

  int off = choices[0].second;
  // number + offset % remaining
  temp = -1;

  while (choices.size() > 0) {
    // for (eliminated=0; eliminated < choices[round].first; eliminated++) {}
    temp = (temp + off) % choices.size();
    off = choices[(temp + 1) % choices.size()].second;
    choices.erase(choices.begin() + temp);
    temp--;
    // cout << "temp:" << temp << " off:" << off << " size:" << choices.size() << endl;
  }

  cout << choices[0].first + 1 << endl;



  return 0;
}
