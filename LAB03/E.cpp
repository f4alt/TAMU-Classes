#include <bits/stdc++.h>

using namespace std;

int main() {
  int max_dif, men_total=0, wo_total=0;
  string temp;
  char person1, person2;
  list<char> people_list;

  cin >> max_dif >> temp;

  for (int i=0; i < temp.size(); i++) {
    people_list.push_back(temp[i]);
  }

  while (!people_list.empty() && abs(men_total - wo_total) <= max_dif) {
    std::list<char>::iterator it1;
    // for (it1=people_list.begin(); it1!=people_list.end(); ++it1)
    //   std::cout << ' ' << *it1;
    // std::cout << wo_total + men_total << '\n';

    person1 = people_list.front();
    // cout << person1 << endl;

    if (person1 == 'M' && abs(men_total+1 - wo_total) <= max_dif) {
      // cout << "adding man" << endl;
      men_total++;
      people_list.pop_front();
    } else if (person1 == 'W' && abs(wo_total+1 - men_total) <= max_dif) {
      // cout << "adding women" << endl;
      wo_total++;
      people_list.pop_front();
    } else if (people_list.size() > 1) {
      list<char>::iterator ptr2 = std::next(people_list.begin());
      person2 = *ptr2;
      // cout << person2 << endl;
      if (person2 == 'M' && abs(men_total+1 - wo_total) <= max_dif) {
        men_total++;
        // people_list.pop_front();
        people_list.erase(ptr2);
      } else if (person2 == 'W' && abs(wo_total+1 - men_total) <= max_dif) {
        wo_total++;
        // people_list.pop_front();
        people_list.erase(ptr2);
      } else {
        // men_total++;
        break;
      }
    }
  }

  cout << men_total + wo_total << endl;


  return 0;
}
