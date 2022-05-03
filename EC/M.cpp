#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, q;
  map<int, set<string> > prob;
  map<string, int> people;

  cin >> n;

  while (n--) {
    string name;
    int pos;
    cin >> name >> pos;
    people.insert(make_pair(name, pos));
    if (prob.find(pos) != prob.end()) {
      // cout << "found: " << pos << endl;
      prob[pos].insert(name);
    } else {
      set<string> temp;
      temp.insert(name);
      // cout << "creating: " << pos << " | " << name << endl;
      prob.insert(make_pair(pos, temp));
    }
  }

  // for (auto i : prob) {
  //   cout << i.first << ":";
  //   for (auto j : i.second) {
  //     cout << j << " ";
  //   }
  //   cout << endl;
  // }

  map<int, pair<int, int> > ps;
  int rt = 0;
  for (auto i : prob) {
    ps.insert(make_pair(i.first, make_pair(rt, rt + i.second.size()-1)));
    rt += i.second.size();
  }

  // cout << endl;
  // for (auto i : ps) {
  //   cout << i.first << ":" << i.second.first << " | " << i.second.second << endl;
  // }

  cin >> q;

  while (q--) {
    string one, two;
    cin >> one >> two;

    int onei = people[one];
    int twoi = people[two];

    int lower = min(min(abs(ps[onei].first - ps[twoi].first),
                    abs(ps[onei].second - ps[twoi].second)),
                    min(abs(ps[onei].first - ps[twoi].second),
                    abs(ps[onei].second - ps[twoi].first)));
    int upper = max(max(abs(ps[onei].first - ps[twoi].first),
                    abs(ps[onei].second - ps[twoi].second)),
                    max(abs(ps[onei].first - ps[twoi].second),
                    abs(ps[onei].second - ps[twoi].first)));

    if (onei < twoi) {
      cout << one << " is " << lower << "-" << upper << " rank(s) below " << two << "!" << endl;
    } else if (onei > twoi) {
      cout << one << " is " << lower << "-" << upper << " rank(s) above " << two << "!" << endl;
    } else {
      cout << one << " is tied with " << two << "!" << endl;
    }

  }







  return 0;
}
