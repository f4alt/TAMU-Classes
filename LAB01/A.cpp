#include <iostream>
#include <string.h>

using namespace std;

int main() {
  string in_str;
  string response_str;

  cin >> in_str;

  int i=0;
  while (i != in_str.size()) {
    if (i+2 < in_str.size() && in_str[i] != in_str[i+1] && in_str[i] != in_str[i+2] && in_str[i+1] != in_str[i+2]) {
      response_str.append("C");
      i += 3;
    } else {
      if (in_str[i] == 'R')
        response_str.append("S");
      else if (in_str[i] == 'B')
          response_str.append("K");
      else if (in_str[i] == 'L')
          response_str.append("H");
      i++;
    }
  }

  cout << response_str << endl;
}
