#include <bits/stdc++.h>

using namespace std;

int main() {
   priority_queue<long long> left;
   priority_queue<long long, vector<long long>, std::greater<long long>> right;
   string temp;
   long long in;

   while(!cin.eof()) {
     cin >> temp;

     if (temp[0] == '#') {
       if (left.size() > right.size()) {
         cout << left.top() << endl;
         left.pop();
       } else {
         if (!right.empty()) {
           cout << right.top() << endl;
           right.pop();
         }
       }
       // if (!right.empty()) {
       //   cout << right.top() << endl;
       //   right.pop();
       // }
     } else {
       in = stoi(temp);
       if (right.empty() || in > right.top()) {
         right.push(in);
       }
       else {
         left.push(in);
       }
       if (right.size() > left.size() + 1) {
         // cout << "pushing:" << right.top() << endl;
         left.push(right.top());
         right.pop();
       }
       if (left.size() > right.size()) {
         right.push(left.top());
         left.pop();
       }
     }
   }

   // cout << endl;
   // cout << left.size() << " | " << right.size() << endl;
   // cout << endl;
   //
   // while (!left.empty()) {
   //   cout << left.top() << endl;
   //   left.pop();
   // }
   // cout << endl;
   // while (!right.empty()) {
   //   cout << right.top() << endl;
   //   right.pop();
   // }


  return 0;
}
