#include <bits/stdc++.h>

using namespace std;

int timem, timel;

bool works1(int first, int second, int third, int fourth) {
  int temp1=0, temp2=0;

  temp1 = abs(first) + abs(first - second);
  // cout << "temp1:" << temp1 << endl;
  if (temp1 <= timem) {
    temp2 = temp1 + abs(second - third) + abs(third - fourth);
    // cout << "temp2:" << temp2 << endl << endl;
    if (temp2 <= timel) {
      return true;
    }
  }

  return false;
}

bool works2(int first, int second, int third, int fourth) {
  int temp1=0, temp2=0;

  // drop first at second and take second to dest
  temp1 = abs(first) + abs(first - second) + abs(second - fourth);
  // cout << "temp1:" << temp1 << endl;
  if (temp1 <= timel) {
    temp2 = temp1 + abs(fourth - second) + abs(second - third);
    // cout << "temp2:" << temp2 << endl << endl;
    if (temp2 <= timem) {
      return true;
    }
  }

  return false;
}

int main() {
  int m, l, M, L;

  cin >> m >> l >> M >> L >> timem >> timel;

  // if (works1(m, M, l, L) ||
  //     works1(l, L, m, M) ||
  //     works2(m, l, L, M) ||
  //     works2(l, m, M, L) ) {
  if(abs(m)+abs(m-M) <= timem && abs(m)+abs(m-M)+abs(M-l)+abs(l-L) <= timel){
    cout << "possible" << endl;
  } else if(abs(l)+abs(l-L) <= timel && abs(l)+abs(l-L)+abs(L-m)+abs(m-M) <= timem){
    cout << "possible" << endl;
  } else if(abs(m)+abs(m-l)+abs(l-L) <= timel && abs(m)+abs(m-l)+abs(l-L)+abs(L-l)+abs(l-M) <= timem){
    cout << "possible" << endl;
  } else if(abs(l)+abs(l-m)+abs(m-M) <= timem && abs(l)+abs(l-m)+abs(m-M)+abs(M-m)+abs(m-L) <= timel){
    cout << "possible" << endl;
  } else {
    cout << "impossible" << endl;
  }














  return 0;
}
