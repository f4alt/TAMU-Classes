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
    // cout << "first:" << parent << endl;

    if (parent == "def") {
      cin >> word >> val;
      // cout << "def found" << endl;

      it = words.find(word);
      if (it == words.end()) {
        // words.push( {word, val } );
        words.insert(make_pair(word, val));
        words_rev.insert(make_pair(val, word));
      } else {
        it->second = val;
      }
    } else if (parent == "calc") {
      string path="";
      cin >> word;
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
      break;
    }
  }






  return 0;
}
