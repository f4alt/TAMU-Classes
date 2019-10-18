#include <iostream>
#include <fstream>
#include "functions.h"
#include "provided.h"

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;

int main() {
  // Input variables
  int ngames;
  int duration;
  int start_date;
  char titles[50];
  char preferences[50];
  char plan[50];
  char gameTitles[MAX_NB_GAMES][MAX_TITLE_SIZE];

  // Input data with cin
  cout << "Please enter ngames and duration: ";
  cin >> ngames >> duration;
  // check input data
  if (ngames < 0 || ngames > 200 || duration < 0 || duration > 365) {
    cout << "Invalid input." << endl;
    return -1;
  }
  cout << "Please enter name of file with titles: ";
  cin >> titles;
  cout << "Please enter name of file with preferences: ";
  cin >> preferences;
  cout << "Please enter name of file with plan: ";
  cin >> plan;
  // check titles
  ifstream intitles;
  ifstream inpref;
  ifstream inplan;
  intitles.open(titles);
  inpref.open(preferences);
  inplan.open(plan);
  if (!intitles || !inpref || !inplan) {
    cout << "Invalid file." << endl;
    return -1;
  }
  intitles.close();
  inpref.close();
  inplan.close();

  // create prefs array and zero out
  int prefs_array[MAX_NB_GAMES];
  for (int i = 0; i < MAX_NB_GAMES; i++) {
    prefs_array[i] = 0;
  }

  // create plan array and zero out
  int plan_array[366];
  for (int i = 0; i < 366; i++) {
    plan_array[i] = 0;
  }

  // use inputs
  readGameTitles(titles, ngames, gameTitles);
  readPrefs(preferences, ngames, prefs_array);
  readPlan(plan, ngames, plan_array);
  start_date = findBestVacation(duration, prefs_array, ngames, plan_array);

  // output findings
  cout << "Best start day is " << start_date << endl;
  cout << "Games to be played: " << endl;
  printGamesPlayedInVacation(start_date, duration, plan_array,
    gameTitles, ngames);

  return 0;
}
