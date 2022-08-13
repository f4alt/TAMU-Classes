#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//reads game preferences from file
//returns -1 if error opening file
int readPrefs(char fileName[], int ngames, int prefs[]);

//reads cousins plan
int readPlan(char fileName[], int ngames, int plan[]);

//returns the ratings for games played
int computeFunLevel(int start, int duration, int prefs[], int ngames,
  int plan[]);

//returns earliest start date for highest fun level
int findBestVacation(int duration, int prefs[], int ngames, int plan[]);

#endif
