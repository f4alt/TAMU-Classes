#include <bits/stdc++.h>

using namespace std;

int main() {
  string card = "";
  map<char, int> card_freq;
  std::map<char,int>::iterator it = card_freq.begin();

  for (int i=0; i < 5; i++) {
    cin >> card;

    it = card_freq.find(card[0]);
    if (it != card_freq.end()) {
      it->second++;
    } else {
      card_freq.insert ( std::pair<char,int>(card[0],1) );
    }
  }
  char most;
  int mostQ=0;
  for (it = card_freq.begin(); it != card_freq.end(); it++) {
    if (it->second > mostQ) {
      most = it->first;
      mostQ = it->second;
    }
  }

  cout << mostQ;
}
