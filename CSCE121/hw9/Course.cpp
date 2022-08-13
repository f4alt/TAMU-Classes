#include <iostream>
#include <fstream>
#include <string>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"

using namespace std;

Course::Course(string id, string title, Date startTime, Date endTime)
: id(id), title(title), startTime(startTime), endTime(endTime) {}

string Course::getID() {
  return this->id;
}

string Course::getTitle() {
  return this->title;
}

Date Course::getStartTime() {
  return this->startTime;
}

Date Course::getEndTime() {
  return this->endTime;
}

void Course::addAttendanceRecord(AttendanceRecord ar) {
  attendanceRecords.push_back(ar);
}

// default outputAttendance
void Course::outputAttendance() {
  for (int i = 0; i < attendanceRecords.size(); i++) {
    int month = attendanceRecords[i].getDate().getMonth();
    int day = attendanceRecords[i].getDate().getDay();
    int year = attendanceRecords[i].getDate().getYear();
    int hour = attendanceRecords[i].getDate().getHour();
    int min = attendanceRecords[i].getDate().getMin();
    int sec = attendanceRecords[i].getDate().getSec();
    string month_s = to_string(month);
    string day_s = to_string(day);
    string hour_s = to_string(hour);
    string min_s = to_string(min);
    string sec_s = to_string(sec);
    string section = attendanceRecords[i].getCourseID();
    string uin = attendanceRecords[i].getStudentID();

    // convert single digits to have leading 0 if necessary
    if (hour < 10) {
      hour_s = '0' + hour_s;
    }
    if (min < 10) {
      min_s = '0' + min_s;
    }
    if (sec < 10) {
      sec_s = '0' + sec_s;
    }

    cout << month_s << "/" << day_s << "/" << year << " " << hour_s << ":"
    << min_s << ":" << sec_s << "," << section << "," << uin << endl;
  }
}

// paramaterized outputAttendance
void Course::outputAttendance(string student_id) {
  bool has_output = false;
  for (int i = 0; i < attendanceRecords.size(); i++) {
    if (attendanceRecords[i].getStudentID() == student_id) {
      int month = attendanceRecords[i].getDate().getMonth();
      int day = attendanceRecords[i].getDate().getDay();
      int year = attendanceRecords[i].getDate().getYear();
      int hour = attendanceRecords[i].getDate().getHour();
      int min = attendanceRecords[i].getDate().getMin();
      int sec = attendanceRecords[i].getDate().getSec();
      string month_s = to_string(month);
      string day_s = to_string(day);
      string hour_s = to_string(hour);
      string min_s = to_string(min);
      string sec_s = to_string(sec);
      string section = attendanceRecords[i].getCourseID();
      string uin = attendanceRecords[i].getStudentID();

      // convert single digits to have leading 0 if necessary
      if (hour < 10) {
        hour_s = '0' + hour_s;
      }
      if (min < 10) {
        min_s = '0' + min_s;
      }
      if (sec < 10) {
        sec_s = '0' + sec_s;
      }

      cout << month_s << "/" << day_s << "/" << year << " " << hour_s << ":"
      << min_s << ":" << sec_s << "," << section << "," << uin << endl;
      has_output = true;
    }
  }
  if (has_output == false) {
    cout << "No Records" << endl;
  }
}
