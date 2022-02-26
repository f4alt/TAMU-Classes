#include <bits/stdc++.h>

using namespace std;

int main() {
  string parent, word;
  int val, sum;
  map<string, int> words;
  map<string, int>::iterator it;
  map<int, string> words_rev;
  map<int, string>::iterator itr;

  while (!cin.eof()) {
    cin >> parent;
    // cout << "parent:" << parent << endl;

    if (parent == "def") {
      cin >> word >> val;
      if (word == "") {
        break;
      }

      it = words.find(word);
      if (it == words.end()) {
        words.insert(make_pair(word, val));
        words_rev.insert(make_pair(val, word));
      } else {
        words_rev.erase(it->second);
        it->second = val;
        words_rev.insert(make_pair(val, word));
      }
    } else if (parent == "calc") {
      string path="";
      cin >> word;
      // cout << "word:" << word << endl;
      if (word == "" || word == "=") {
        break;
      }
      sum = 0;
      bool unknown = false;
      bool add_found = true;
      while (word != "=") {
        // cout << "curr:" << word << endl;
        path.append(word);
        path.append(" ");

        if (word == "+") {
          add_found = true;
        } else if (word == "-") {
          add_found = false;
        } else {
          it = words.find(word);
          if (it != words.end()) {
            // cout << it->first << " found" << endl;
            if (add_found) {
              sum += it->second;
            } else {
              sum -= it->second;
            }
          } else {
            // cout << "unknown" << endl;
            unknown = true;
          }
        }
        cin >> word;
      }
      if (!unknown) {
        // cout << sum << endl;
        itr = words_rev.find(sum);
        if (itr != words_rev.end()) {
          cout << path << "= " << itr->second << endl;
        } else {
          cout << path << "= unknown" << endl;
        }
      } else {
        cout << path << "= unknown" << endl;
      }

    } else {
      // cout << "CLEARING" << endl;
      words.clear();
      words_rev.clear();
      // break;
    }

    // sanity prints
    // cout << "prints" << endl;
    // for (auto i : words) {
    //   cout << i.first << " : " << i.second << endl;
    // }
    // for (auto i : words_rev) {
    //   cout << i.first << " : " << i.second << endl;
    // }
    // cout << "end prints" << endl << endl;
  }






  return 0;
}
