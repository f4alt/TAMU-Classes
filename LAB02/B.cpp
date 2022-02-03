#include <bits/stdc++.h>

using namespace std;

vector< pair <string, vector<string> > > breakInto(vector<string> list) {
  vector< pair <string, vector<string> > > ret;
  vector<string> name, heir;
  string curr, to_add="";

  for (int i=0; i < list.size(); i++) {
      curr = list[i];

      for (int j=0; j < curr.size(); j++) {
        if (curr[j] == ':') {
          name.push_back(to_add);
          to_add = "";
          continue;
        }
        if (curr[j] == '-') {
          heir.push_back(to_add);
          to_add = "";
          // continue;
        }

        if (curr[j] == ' ') {
          continue;
        } else if (curr[j] == '-') {
          continue;
        } else {
          to_add.insert(to_add.end(), curr[j]);
        }
      }
      if (to_add != "") {
        heir.push_back(to_add);
        to_add = "";
      }
      if (name[0] != "" && heir.size() > 0) {
        ret.push_back({name[0], heir});
        name.clear();
        heir.clear();
      }
  }

  return ret;
}

void sort_print(vector< pair <string, vector<string> > > list) {
  string name_temp;
  vector<string> heir_temp;

  // cout << "---" << endl;
  // for (int i=0; i < list.size(); i++) {
  //   cout << list[i].first << endl;
  // }

  for (int i=0; i < list.size()-1; i++) {
    for (int j=0; j < list.size()-i-1; j++) {
      // cout << list[j].first << " vs " << list[j+1].first << " | " << endl;
      for (int k=0; k < min(list[j].second.size(), list[j+1].second.size()); k++) {
        // cout << "loop size:" << min(list[j].second.size(), list[j+1].second.size()) << endl;
        string check1 = list[j].second[list[j].second.size() - k - 1];
        string check2 = list[j+1].second[list[j+1].second.size() - k - 1];
        // cout << check1 << " vs " << check2 << endl;
        if (check1 != check2) {
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
        }
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
  }

  // cout << "..." << endl;
  for (int i=0; i < list.size(); i++) {
    cout << list[i].first << endl;
  }
}

int main() {
  int qnty, loop;
  vector<string> upper_raw, middle_raw, lower_raw;
  vector< pair <string, vector<string> > > upper, middle, lower;
  string name, order, class_end, temp;

  // std::ios::sync_with_stdio(false);
  // cin.tie(NULL);
  // cout.tie(NULL);

  cin >> qnty;

  for (int i=0; i<qnty; i++) {
    cin >> loop;

    for (int j=0; j<loop; j++) {
      cin >> name >> order >> class_end;
      // cin >> temp;

      // cout << name << endl;
      // cout << order << endl;
      // cout << class_end << endl;
      // cout << endl;

      // break into smaller lists
      // cout << "temp:" << temp << " | " << temp[temp.size() -9] << endl;
      if (order[order.size() -3] == 'd') {
        // cout << "here" << endl;
        middle_raw.push_back(name);
        middle_raw.push_back(order);
      }
      if (order[order.size() -3] == 'p') {
        upper_raw.push_back(name);
        upper_raw.push_back(order);
      }
      if (order[order.size() -3] == 'w') {
        lower_raw.push_back(name);
        lower_raw.push_back(order);
      }

    }
    // split
    upper = breakInto(upper_raw);
    middle = breakInto(middle_raw);
    lower = breakInto(lower_raw);

    // sort
    if (!upper.empty()) {
      sort_print(upper);
    }
    if (!middle.empty()) {
      sort_print(middle);
    }
    if (!lower.empty()) {
      sort_print(lower);
    }
    cout << "==============================" << endl;
    upper.clear();
    middle.clear();
    lower.clear();
    upper_raw.clear();
    middle_raw.clear();
    lower_raw.clear();
  }

  // cout << "---" << endl;
  // for (int i=0; i < upper.size(); i++) {
  //   cout << upper[i].first << endl;
  //   // for (int j=0; j < upper[i].second.size(); j++) {
  //   //   cout << upper[i].second[j] << endl;
  //   // }
  // }
  // // cout << endl;
  // for (int i=0; i < middle.size(); i++) {
  //   cout << middle[i].first << endl;
  //   // for (int j=0; j < middle[i].second.size(); j++) {
  //   //   cout << middle[i].second[j] << endl;
  //   // }
  // }
  // // cout << endl;
  // for (int i=0; i < lower.size(); i++) {
  //   cout << lower[i].first << endl;
  //   // for (int j=0; j < lower[i].second.size(); j++) {
  //   //   cout << lower[i].second[j] << endl;
  //   // }
  // }


  return 0;
}
