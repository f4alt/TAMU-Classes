#include <bits/stdc++.h>

using namespace std;

// A

int main() {
  unordered_map<string, int> places;
  std::unordered_map<std::string,int>::const_iterator it;
  vector<priority_queue <int>> places_years_pq;
  vector<vector<int>> places_years_vec;
  // vector<priority_queue<int, vector<int>, std::greater<int> > > places_years;
  int trips, queries;
  string place;
  int year;
  int iterator=0;

  // while (!cin.eof()) {
    cin >> trips;

    for (int i=0; i < trips; i++) {
      cin >> place >> year;

      it = places.find(place);
      if (it == places.end()) {
        places.insert({ place, iterator });
        priority_queue<int> pq;
        // priority_queue<int, vector<int>, std::greater<int> > pq;
        pq.push(-year);
        places_years_pq.push_back(pq);
        iterator++;

        // cout << "place inserted:" << place << " at " << iterator-1 << endl;
      } else {
        // cout << "pushing at " << it->second << ":" << year << endl;
        places_years_pq[it->second].push(-year);
      }
    }

    for (int i=0; i < places_years_pq.size(); i++) {
      // cout << "size1:" << places_years_pq.size() << endl;
      vector<int> temp;
      // for (int j=0; j < places_years_pq[i].size()-1; j++) {
      while (!places_years_pq[i].empty()) {
        // cout << "size2:" << places_years_pq[i].size() << endl;
        // cout << "pushing:" << -places_years_pq[i].top() << endl;
        temp.push_back(-places_years_pq[i].top());
        places_years_pq[i].pop();
      }
      places_years_vec.push_back(temp);
    }

    cin >> queries;
    for (int i=0; i < queries; i++) {
      cin >> place >> year;

      it = places.find(place);
      //
      // priority_queue<int> temp = places_years[it->second];
      // // priority_queue<int, vector<int>, std::greater<int> > temp = places[it->second];
      // for (int j=0; j<year-1; j++) {
      //   temp.pop();
      // }
      // cout << -temp.top() << endl;
      cout << places_years_vec[it->second][year-1] << endl;
    }

  // }



  return 0;
}
