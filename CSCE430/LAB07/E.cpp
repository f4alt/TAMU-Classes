#include <bits/stdc++.h>

using namespace std;

struct room {
  int val;
  int idx;
};

int cmp(const void* a, const void* b) {
  return ((room*)b)->val - ((room*)a)->val;
}

int main() {
  int n, sum=0;
  cin >> n;

  room exams[n];
  // vector<room> exams(n);

  for (int i = 0; i < n; i++) {
    cin >> exams[i].val;
    exams[i].idx = i + 1;
    sum += exams[i].val;
  }
  qsort(exams, (size_t)n, sizeof(room), cmp);

  if (sum < exams[0].val << 1) {
    cout << "impossible" << endl;
  } else {
    cout << exams[0].idx;
    for (int i = 1; i < n; i++) {
      cout << " " << exams[i].idx;
    }
    cout << endl;
  }
  return 0;
}
