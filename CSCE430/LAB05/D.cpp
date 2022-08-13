#include <bits/stdc++.h>

using namespace std;

map<int, vector<int> > order;
map<int, vector<int> >::iterator it;

int findchild(int i) {
  cout << "looking for:" << i << endl;
  it = order.find(i);
  if (it != order.end()) {
    findchild(it->second[0]);
    // i = it->second[0];
  } else {
    return i;
  }
}

int main() {
  int queries, first, second;
  vector<string> input;
  // vector<int> order;
  string temp;


  cin >> queries;

  for (int i=0; i < queries; i++) {
    cin >> temp;
    input.push_back(temp);
  }
  for (int i=0; i < queries-1; i++) {
    cin >> first >> second;

    it = order.find(first);
    if (it != order.end()) {
      it->second.push_back(second);
    } else {
      vector<int> temp_vec;
      temp_vec.push_back(second);
      order.insert(make_pair(first, temp_vec));
    }
  }

  for ( auto i : order) {
    for (int j=0; j < i.second.size(); j++) {
      // cout << "j:" << i.second[j] << endl;

      // cout << input[i.second[j]-1];
      findchild(i.second[j]);
    }
  }
  cout << endl;



  return 0;
}
