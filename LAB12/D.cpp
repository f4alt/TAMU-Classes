#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// D

int main() {
  long long n, m;

  cin >> n >> m;

  long long currNode=2, currWeight=1;
  long long ans = 0;

  while (currNode <= n) {
    ans += currWeight;
    currWeight++;
    m--;
    long long waste = max(0LL, currNode-2);
    long long need = n-currNode;
    waste = min(waste, m-need);
    m -= waste;
    currWeight += waste;
    currNode = currNode+1;
  }

  cout << ans << endl;
}
