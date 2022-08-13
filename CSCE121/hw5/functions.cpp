#include <iostream>
#include <fstream>
#include <cstring>
#include "functions.h"

using std::ifstream;
using namespace std; //delete

//reads game preferences from file
//returns -1 if error opening file
int readPrefs(char fileName[], int ngames, int prefs[]) {
  int validGames = 0;
  int gameid;
  int rating;

  ifstream fin;
  fin.open(fileName);
  if (!fin) {
    return -1;
  }
  for (int i = 0; i < ngames; i++) {
    fin >> gameid;
    // cout << "gameid " << gameid << endl; //testline
    if (fin.good()) {
      if (gameid >= 0 && gameid < 200) {
        fin >> rating;
        // cout << "rating " << rating << endl; //testline
        prefs[gameid] = rating;
        validGames++;
      } else {
        fin >> rating;
      }
    }
  }
  return validGames;
}

// reads cousins plan
int readPlan(char fileName[], int ngames, int plan[]) {
  int date;
  int gameid;

  ifstream fin;
  fin.open(fileName);
  if (!fin) {
    return -1;
  }
  for (int i = 1; i < 366; i++) {
    fin >> date;
    if (fin.good()) {
      if (date > 0 && date < 366) {
        fin >> gameid;
        plan[date] = gameid;
      } else {
        fin >> gameid;
      }
    } else {
      fin.clear();
    }
  }
  return 0;
}

//returns the ratings for games played
int computeFunLevel(int start, int duration, int prefs[], int ngames,
  int plan[]) {
    int gameid;
    int date = start;
    int fun_total = 0;

    if (duration + start > 366) {
      return - 1;
    } else {
      for (int i = 0; i < duration; i++) {
        gameid = plan[date + i];
        fun_total += prefs[gameid];
      }
    }
    return fun_total;
  }

//returns earliest start date for highest fun level
int findBestVacation(int duration, int prefs[], int ngames, int plan[]) {
  int best_start_date = 1;
  int max_fun_level = 0;
  int check_fun_level = 0;

  max_fun_level = computeFunLevel(1, duration, prefs, ngames, plan);
  for (int i = 1; i < 366; i++) {
    check_fun_level = computeFunLevel(i, duration, prefs, ngames, plan);
    if (check_fun_level > max_fun_level) {
      max_fun_level = check_fun_level;
      best_start_date = i;
    }
  }
  return best_start_date;
}
