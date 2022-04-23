#include <bits/stdc++.h>

using namespace std;

// class node {
// public:
//   bool isin;
//   vector<node*> ch[26];
//   int touched;
//
//   node() {
//     isin = false;
//     touched = 0;
//     for (int i=0; i < 26; i++) ch[0][i] = NULL;
//   }
//
//   // void add (string s) {
//   //   if (s.length() == 0) {
//   //     isin = true;
//   //     return;
//   //   }
//   //   char c = s[0];
//   //   if (ch[c-'A'] == NULL) {
//   //     ch[c-'A'] = new node();
//   //   }
//   //
//   //   string s2 = s.substr(1);
//   //   ch[c-'A']->add(s2);
//   // }
//
//   int add(int idx, string s) {
//       int c = s.back() - 'a';
//       // cout << (char)(c+'a') << endl;
//       cout << c << endl;
//       s.pop_back();
//
//       if (ch[idx][c] == NULL) {
//         ch[idx][c] = new node();
//       }
//
//       int ans = ch[idx][c]->touched;
//       cout << "ans: " << ans << endl;
//       ch[idx][c]->touched++;
//
//       if (s.size() == 0) {
//         isin = true;
//         return ans;
//       }
//
//       return add(idx+1, s);
//   }
//
//   // void printout(string s = "") {
//   //   if (isin) {
//   //     cout << s << endl;
//   //   }
//   //   string s2;
//   //   for (int i=0; i < 26; i++) {
//   //     if (ch[i] != NULL) {
//   //       // cout << "here " << s << endl;
//   //       s2 = s + (char)(i+'a');
//   //       ch[i]->printout(s2);
//   //     }
//   //   }
//   // }
// };
struct node {
  bool isin = false;
  int sub = 0;
  vector<node*> next;
};

int add(node* root, string s) {
    int c = s.back() - 'a';
    s.pop_back();

    if (root->next[c] == NULL) {
      root->next[c] = new node;
      root->next[c]->next.resize(26, NULL);
    }

    int ret = root->next[c]->sub;
    root->next[c]->sub++;

    if (s.size() == 0) {
      root->isin = true;
      return ret;
    }

    return add(root->next[c], s);
}


int main() {
  int n;
  node* trie = new node;
  trie->next.resize(26, NULL);

  cin >> n;

  while (n--) {
    string s;
    cin >> s;
    reverse(s.begin(), s.end());

    cout << add(trie, s) << endl;
  }
  // string s;
  // while (true) {
  //   cin >> s;
  //   if (s == "DONE") {
  //     break;
  //   }
  //
  //   trie.add(s);
  // }
  //
  // cout << "dict:" << endl;
  // trie.printout();












  return 0;
}
