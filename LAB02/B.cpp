#include <bits/stdc++.h>

using namespace std;

void sort_print(vector< pair <string, vector<string> > > list) {
  string name_temp;
  vector<string> heir_temp;

  for (int i=0; i < list.size(); i++) {
    for (int j=0; j < list.size()-i-1; j++) {

      // only compare against lowest equals
      for (int k=0; k < min(list[j].second.size(), list[j+1].second.size()); k++) {
        // cout << "loop size:" << min(list[j].second.size(), list[j+1].second.size()) << endl;
        string check1 = list[j].second[list[j].second.size() - k - 1];
        string check2 = list[j+1].second[list[j+1].second.size() - k - 1];
        // cout << check1 << " vs " << check2 << endl;
        if (check1 == "upper" && check2 != "upper") {
          break;
        }
        if (check1 == "middle" && check2 == "lower") {
          break;
        }
        // if (check1 != check2) {
          if (check1 == "middle" && check2 == "upper") {
            // cout << "here:" << list[j].first << " vs " << list[j+1].first << endl;
            name_temp = list[j+1].first;
            heir_temp = list[j+1].second;
            list[j+1].first = list[j].first;
            list[j+1].second = list[j].second;
            list[j].first = name_temp;
            list[j].second = heir_temp;
            // cout << "hereafter:" << list[j].first << " vs " << list[j+1].first << endl;
            break;
          }
          if (check1 == "lower" && check2 != "lower") {
            // cout << "here:" << list[j].first << " vs " << list[j+1].first << endl;
            name_temp = list[j+1].first;
            heir_temp = list[j+1].second;
            list[j+1].first = list[j].first;
            list[j+1].second = list[j].second;
            list[j].first = name_temp;
            list[j].second = heir_temp;
            // cout << "hereafter:" << list[j].first << " vs " << list[j+1].first << endl;
            break;
          }
        // }
        if (k+1 == min(list[j].second.size(), list[j+1].second.size())) {
          if (list[j].first > list[j+1].first) {
            name_temp = list[j+1].first;
            heir_temp = list[j+1].second;
            list[j+1].first = list[j].first;
            list[j+1].second = list[j].second;
            list[j].first = name_temp;
            list[j].second = heir_temp;
            // cout << "hereafter:" << list[j].first << " vs " << list[j+1].first << endl;
            break;
          }
        }
      }
    }
    // cout << endl;
  }

  for (int i=0; i < list.size(); i++) {
    cout << list[i].first << endl;
  }
}

int main() {
  int qnty, loop;
  vector<string> in_raw;
  vector< pair <string, vector<string> > > classes;
  string name, order, class_end;

  // std::ios::sync_with_stdio(false);
  // cin.tie(NULL);
  // cout.tie(NULL);

  cin >> qnty;

  for (int i=0; i<qnty; i++) {
    cin >> loop;

    for (int j=0; j<loop; j++) {
      cin >> name >> order >> class_end;

      // string stream input to - deliminate
      stringstream s_stream(order);
      while (s_stream.good()) {
        string substr;
        getline(s_stream, substr, '-');
        if (substr != "") {
          in_raw.push_back(substr);
        }
      }

      name.erase(name.size()-1);
      classes.push_back({name, in_raw});

      in_raw.clear();

    }
    if (!classes.empty()) {
      sort_print(classes);
    }
    cout << "==============================" << endl;

    classes.clear();
    in_raw.clear();
  }

  return 0;
}
