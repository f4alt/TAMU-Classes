#include <iostream>
#include <string.h>
#include <map>

using namespace std;

int main() {
  int correct=0, score=0;
  int time=0;
  char answer;
  string is_correct;
  // answer , attempts
  map<char, int> given_answers;

  while (time != -1) {
    cin >> time;
    if (time == -1) {
      break;
    }
    cin >> answer >> is_correct;

    if (is_correct == "right") {
      correct++;
      score += time;
      for (auto item:given_answers) {
        if (item.first == answer) {
          score += (item.second * 20);
        }
      }
    } else {
      std::map<char, int>::iterator it = given_answers.find(answer);
      if (it != given_answers.end()) {
        it->second++;
      } else {
        given_answers.insert(std::make_pair(answer, 1));
      }
    }
  }

  cout << correct << " " << score << endl;
}
