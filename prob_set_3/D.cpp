#include <bits/stdc++.h>

using namespace std;

int main() {
  // set_intersection(set1.begin(),
  // set1.end(),
  // set2.begin(),
  // set2.end(),
  // inserter(result, result.begin()));

  map<string, set<string>>::iterator it;
  int test_cases, pizzas, ingredients;
  string temp;

  cin >> test_cases;
  for (int z=0; z < test_cases; z++) {
    cin >> pizzas;

    // reset
    map<string, set<string>> e, f;

    // take in english and foreign ingredient names
    for (int x=0; x < pizzas; x++) {
      cin >> temp; // throw away pizza name
      // cout << "pizza:" << x << endl;
      // reset
      vector<string> english_names, foreign_names;
      set<string> foreign_set, english_set;

      // take in x english ingredients
      cin >> ingredients;
      for (int i=0; i < ingredients; i++) {
        cin >> temp;
        english_names.push_back(temp);
        english_set.insert(temp);
      }

      // take in x foreign lang ingredients
      cin >> ingredients;
      for (int i=0; i < ingredients; i++) {
        cin >> temp;
        foreign_names.push_back(temp);
        foreign_set.insert(temp);
      }

      // assign all possibilities to map
      for (int i=0; i < english_names.size(); i++) {
        it = e.find(english_names[i]);
        if (it == e.end()) {
          e.insert( { english_names[i], foreign_set } );
        } else { // set subtraction
          set<string> result;
          set_intersection(it->second.begin(), it->second.end(), foreign_set.begin(), foreign_set.end(), inserter(result, result.begin()));
          // cout << "found:" << it->first << " -> after set_intersection:";
          // for ( auto i : result) {
          //   cout << i << " ";
          // }
          // cout << endl;
          it->second = result;
        }
      }
      for (int i=0; i < foreign_names.size(); i++) {
        it = f.find(foreign_names[i]);
        if (it == f.end()) {
          f.insert( { foreign_names[i], english_set } );
        } else { // set subtraction
          set<string> result;
          set_intersection(it->second.begin(), it->second.end(), english_set.begin(), english_set.end(), inserter(result, result.begin()));
          it->second = result;
        }
      }

      // sanity print
      // for ( auto i : e ) {
      //   cout << i.first << ":";
      //   for (auto j : i.second) {
      //     cout << j << " ";
      //   }
      //   cout << endl;
      // }
      // cout << endl;
      // for ( auto i : f ) {
      //   cout << i.first << ":";
      //   for (auto j : i.second) {
      //     cout << j << " ";
      //   }
      //   cout << endl;
      // }
      // cout << endl;
    }
    for ( auto map_val : e ) {
      vector<string> final_possiblity;
      // cout << "looking in:" << map_val.first << " |looking for:";
      for (auto foreign_possibility : map_val.second) {
        // cout << foreign_possibility << " ";
        it = f.find(foreign_possibility);
        if (it->second.find(map_val.first) != it->second.end()) {
          // cout << foreign_possibility << " ";
          // remove.push_back(foreign_possibility);
          final_possiblity.push_back(foreign_possibility);
        }
      }
      for (int i=0; i < final_possiblity.size(); i++) {
        cout << "(" << map_val.first << ", " << final_possiblity[i] << ")" << endl;
      }
    }

    // for ( auto i : e ) {
    //   cout << i.first << ":";
    //   for (auto j : i.second) {
    //     cout << j << " ";
    //   }
    //   cout << endl;
    // }
    // cout << endl;
    // for ( auto i : f ) {
    //   cout << i.first << ":";
    //   for (auto j : i.second) {
    //     cout << j << " ";
    //   }
    //   cout << endl;
    // }
    cout << endl;
  }


  return 0;
}
