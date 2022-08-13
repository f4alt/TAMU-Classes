#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include "School.h"
#include "AttendanceRecord.h"

using namespace std;

Date timeToDate(string s_time) {
  istringstream st(s_time);
  string s_hour;
  string s_min;
  // string s_sec;
  string tod;
  int hour;
  int min;
  int sec = 0;
  getline(st, s_hour, ':');
  getline(st, s_min, ':');
  // getline(st, s_sec, ' ');
  // getline(st, tod);

  hour = std::stoi(s_hour);
  min = std::stoi(s_min);
  // sec = std::stoi(s_sec);

  if (tod == "PM") {
    hour += 12;
  }
  // convert numbers to date
  return Date(hour, min, sec);
}

void School::addCourses(string filename) {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    cout << "Unable to open file: " << filename << endl;
    return;
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    // separate first info before comma as date
    string section_id;
    getline(ss, section_id, ',');
    if (section_id == "\0") {
      break;
    }

    // separate next info as start time
    string string_startTime;
    getline(ss, string_startTime, ',');

    // separate last info as end time
    string string_endTime;
    getline(ss, string_endTime, ',');

    // next info is title?
    string title_s;
    getline(ss, title_s, ',');
    // keep adding title and 'and' until end of line
    while (ss) {
      string tempstring;
      getline(ss, tempstring, ',');
      if (ss) {
        title_s += ",";
        title_s += tempstring;
      }
    }

    // convert string start and end times to numbers
    Date startTime = timeToDate(string_startTime);
    Date endTime = timeToDate(string_endTime);

    courses.push_back(Course(section_id, title_s, startTime, endTime));
  }
}

void School::addStudents(string filename) {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    cout << "Unable to open file: " << filename << endl;
    return;
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string uin;
    getline(ss, uin, ',');
    string name;
    getline(ss, name);
    if (!ss.fail()) {
      students.push_back(Student(uin, name));
    }
  }
}

void School::addAttendanceData(string filename) {
    // skeleton based off add couses
    ifstream ifs(filename);
    if (!ifs.is_open()) {
      cout << "Unable to open file: " << filename << endl;
      return;
    }
    while (!ifs.eof()) {
      string line;
      getline(ifs, line);
      istringstream ss(line);
      // separate first info as year ended with -
      string year;
      getline(ss, year, '-');
      // conditional break for some files with extra lines at bottom
      if (year == "\0") {
        break;
      }
      if (year == "\n") {
        break;
      }
      // separate next info as month ended with -
      string month;
      getline(ss, month, '-');
      // next is day ended with space
      string day;
      getline(ss, day, ' ');
      // next is hour ended with :
      string hour;
      getline(ss, hour, ':');
      // next is min ended with :
      string min;
      getline(ss, min, ':');
      // next is sec ended with ,
      string sec;
      getline(ss, sec, ',');
      // next is section_id ended with ,
      string section_id;
      getline(ss, section_id, ',');
      // last is uin
      string uin;
      getline(ss, uin);

      // create date from line
      Date full_date = Date(stoi(year), stoi(month), stoi(day), stoi(hour),
      stoi(min), stoi(sec));
      // create attendance record from line
      AttendanceRecord ar =  AttendanceRecord(section_id, uin, full_date);

      // add created record to courses attendance record
      for (int i = 0; i < courses.size(); i++) {
        if (courses[i].getID() == section_id) {
          if (courses[i].getStartTime() <= full_date
          && courses[i].getEndTime() >= full_date) {
            courses[i].addAttendanceRecord(ar);
          }
        }
      }
    }
}

void School::listCourses() {
  if (courses.size() == 0) {
    cout << "No Courses" << endl;
    return;
  }

  for (int i = 0; i < courses.size(); i++) {
    int start_hour = courses[i].getStartTime().getHour();
    int start_min = courses[i].getStartTime().getMin();
    int end_hour = courses[i].getEndTime().getHour();
    int end_min = courses[i].getEndTime().getMin();
    string start_hour_s = to_string(start_hour);
    string start_min_s = to_string(start_min);
    string end_hour_s = to_string(end_hour);
    string end_min_s = to_string(end_min);

    // if any of the times need a leading 0
    if (start_hour < 10) {
      start_hour_s = '0' + to_string(start_hour);
    }
    if (start_min < 10) {
      start_min_s = '0' + to_string(start_min);
    }
    if (end_hour < 10) {
      end_hour_s = '0' + to_string(end_hour);
    }
    if (end_min < 10) {
      end_min_s = '0' + to_string(end_min);
    }

    // cout statement for all courses
    cout << courses[i].getID() << "," << start_hour_s << ":" << start_min_s <<
    "," << end_hour_s << ":" << end_min_s << "," << courses[i].getTitle()
    << endl;
  }
}

void School::listStudents() {
  if (students.size() == 0) {
    cout << "No Students" << endl;
    return;
  }

  for (int i = 0; i < students.size(); i++) {
    cout << students[i].get_id() << "," << students[i].get_name() << endl;
  }
}

void School::outputCourseAttendance(string course_id) {
  if (courses.size() == 0) {
    cout << "No Records" << endl;
    return;
  }

  for (int i = 0; i < courses.size(); i++) {
    if (courses[i].getID() == course_id) {
      courses[i].outputAttendance();
    }
  }
}

void School::outputStudentAttendance(string student_id, string course_id) {
  if (courses.size() == 0) {
    cout << "No Records" << endl;
    return;
  }

  for (int i = 0; i < courses.size(); i++) {
    if (courses[i].getID() == course_id) {
      courses[i].outputAttendance(student_id);
    }
  }
}
