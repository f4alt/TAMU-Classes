#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

struct toy {
  string name;
  long long qnty;

  toy(string a, long long b) : name(a), qnty(b) {}

  bool operator < (const struct toy& other) const {
    if (qnty == other.qnty) {
      return name > other.name;
    } else {
      return qnty < other.qnty;
    }
  }
};

int main() {

  int tests, numToys, qnty;
  string toyName;
  unordered_map<string, int>::iterator it;

  cin >> tests;
  for (int i=0; i < tests; i++) {
    priority_queue<toy> pq;
    // unordered_map<string, int> toy_comb;
    unordered_map<std::string,int> toy_comb;

    cin >> numToys;

    for (int j=0; j < numToys; j++) {
      cin >> toyName >> qnty;

      it = toy_comb.find(toyName);
      if (it != toy_comb.end()) {
        it->second += qnty;
      } else {
        // toy_comb.insert(make_pair<std::string, int>(toyName, qnty));
        toy_comb.insert( { toyName, qnty } );
      }
    }

    for (auto itr : toy_comb) {
      pq.push(toy(itr.first, itr.second));
    }

    cout << pq.size() << endl;
    while (!pq.empty()) {
      cout << pq.top().name << " " << pq.top().qnty << endl;
      pq.pop();
    }
  }




}
