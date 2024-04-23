#include <iostream>

using namespace std;

class Time {
 public:
  Time();
  Time(string);
  string display() const;
};
class Date {
 public:
  Date();
  Date(string);
  string display() const;
};

/* class DateTime {
  string data;

 public:
  DateTime() : data("1900/01/01 00:00:00") {}
  DateTime(string input) : data(input) {}

  string toString() { return data; }
}; */

class DateTime {
  Date *date;
  Time *time;

 public:
  DateTime() {
    date = new Date("1900/01/01");
    time = new Time("00:00:00");
  }

  DateTime(string s) {
    date = new Date(s.substr(0, 10));
    time = new Time(s.substr(11, 18));
  }

  string toString() {
    return date->display().append(" ").append(time->display());
  }
};