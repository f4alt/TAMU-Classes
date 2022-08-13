#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct params {
    int stocks;
    int schmoney;
    int day;
};

vector<int> inputs;

int dp(int stocks, int schmoney, int day) {
    if (stocks < 0) {
        return -1;
    }
    if (schmoney < 0) {
        return -1;
    }
    if (day < 0) {
        return schmoney;
    }

    params temp;
    temp.stocks = stocks;
    temp.schmoney = schmoney;
    temp.day = day;
    static map<pair<pair<int, int> , int>, int> mydp;
    if (mydp.find(make_pair(make_pair(stocks, schmoney), day)) != mydp.end()) {
        return mydp[make_pair(make_pair(stocks, schmoney), day)];
    }

    int hold = dp(stocks, schmoney, day-1);

    int sell = dp(0,
                  schmoney + stocks * inputs[day],
                  day-1);

    int buy = dp(stocks + schmoney / inputs[day],
                 schmoney - (schmoney / inputs[day]) * inputs[day],
                 day-1);

    int ret = 0;
    if (sell > buy && sell > hold) {
        temp.stocks = 0;
        temp.schmoney = schmoney + stocks * inputs[day];
        temp.day = day-1;
        ret = sell;
    } else if (buy > sell && buy > hold) {
        temp.stocks = stocks + schmoney / inputs[day];
        temp.schmoney = schmoney - (schmoney / inputs[day]) * inputs[day];
        temp.day = day-1;
        ret = buy;
    } else {
        temp.stocks = stocks;
        temp.schmoney = schmoney;
        temp.day = day-1;
        ret = hold;
    }

    mydp[make_pair(make_pair(temp.stocks, temp.schmoney), temp.day)] = ret;
    return ret;
}

int main() {
   long long d, p;
   vector<long long> inputs;
   cin >> d;
   inputs.resize(d, 0);
   for (int i=0; i < d; i++) {
       cin >> inputs[i];
   }
// //    reverse(inputs.begin(), inputs.end());
//    cout << dp(0, 100, d-1) << endl;
  long long numStocks = 0;
  long long schmoney = 100;

  for (int i = 0; i < d - 1; i++) {
    if (inputs[i] < inputs[i + 1]) {
      long long sell = schmoney / inputs[i];
      if (sell + numStocks >= 100000) {
        sell = 100000 - numStocks;
      }
      schmoney -= sell * inputs[i];
      numStocks += sell;
      schmoney += numStocks * inputs[i + 1];
      numStocks = 0;
    }
  }

  cout << schmoney << endl;
}
