#include <bits/stdc++.h>

using namespace std;

int main() {
  int num_teams, queries;

  // map<int, int> team_scores;
  // map<int, int> team_scores_rev;
  vector<pair<long long, int> > scores;
  // map<int, int> positions;
  int one_pos = 1;

  cin >> num_teams >> queries;

  scores.resize(num_teams+1);

  for (int i=1; i <= num_teams; i++) {
    scores[i] = make_pair(0, i);
    // positions.insert( {i,
  }

  for (int i=0; i < scores.size(); i++) {
    cout << i << " :" << scores[i].second << endl;
  }

  int team, penalty;
  while (queries--) {
    cin >> team >> penalty;

    for (int i=1; i < scores.size(); i++) {
      if (scores[i].second == team) {
        scores[i].first += penalty;
        break;
      }
    }

    sort(scores.begin(), scores.end(), cust);

    for (int i=1; i < scores.size(); i++) {
      if (scores[i].second == 1) {
        cout << i << endl;
        break;
      }
    }
  }





  return 0;
}
