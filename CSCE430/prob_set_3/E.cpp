#include <bits/stdc++.h>

using namespace std;

int main() {
  int operations, tempNum;
  string tempOp;
  deque<int> back, front;

  cin >> operations;

  for (int z=0; z < operations; z++) {
    cin >> tempOp >> tempNum;

    if (tempOp == "push_back") {
      front.push_back(tempNum);
    }
    if (tempOp == "push_front") {
      back.push_front(tempNum);
    }
    if (tempOp == "push_middle") {
      front.push_front(tempNum);
    }
    if (tempOp == "get") {
      // cout << "get:";
      if (tempNum < back.size()) {
        cout << back.at(tempNum) << endl;
      } else {
        cout << front.at(tempNum - back.size()) << endl;
      }
    }

    // // sanity queue print
    // cout << "insert:";
    // for (int i=0; i < back.size(); i++) {
    //   cout << back.at(i) << " ";
    // }
    // cout << "| ";
    // for (int i=0; i < front.size(); i++) {
    //   cout << front.at(i) << " ";
    // }
    // cout << endl;

    // balance
    if (front.size() > back.size()) {
      back.push_back(front.front());
      front.pop_front();
    }
    if (back.size() > front.size() + 1) {
      front.push_front(back.back());
      back.pop_back();
    }

    // // sanity queue print
    // cout << "balanced:";
    // for (int i=0; i < back.size(); i++) {
    //   cout << back.at(i) << " ";
    // }
    // cout << "| ";
    // for (int i=0; i < front.size(); i++) {
    //   cout << front.at(i) << " ";
    // }
    // cout << endl;
  }

  // while (!back.empty()) {
  //   cout << back.back() << endl;
  //   back.pop_back();
  // }
  // cout << endl;
  // while (!front.empty()) {
  //   cout << front.back() << endl;
  //   front.pop_back();
  // }

  return 0;
}
