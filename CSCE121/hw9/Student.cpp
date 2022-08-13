#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Student.h"

using namespace std;

Student::Student(string student_id, string name) : id(student_id), name(name) {}

string Student::get_id() {
  return this->id;
}

string Student::get_name() {
  return this->name;
}

void Student::addCourse(string course_id) {
  bool already_in_vector = false;

  // make sure couse id isnt alrady added
  for (int i = 0; i < course_ids.size(); i++) {
    if (course_ids[i] == course_id) {
      already_in_vector = true;
    }
  }

  // resize to +1 and add course_id to end
  if (already_in_vector != true) {
    course_ids.resize(course_ids.size() + 1, course_id);
  }
}

void Student::listCourses() {
  // check if vector is empty
  if (course_ids.size() == 0) {
    cout << "No Records" << endl;
    return;
  }

  cout << "Courses for " << this->id << endl;
  for (int i = 0; i < course_ids.size(); i++) {
    cout << course_ids[i] << endl;
  }
}
