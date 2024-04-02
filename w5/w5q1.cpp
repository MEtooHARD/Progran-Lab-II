#include <iostream>

using namespace std;

class Time {
  int HH = 0, mm = 0, SS = 0;

 public:
  Time() {}

  Time(string t) {
    HH += (t[0] - '0') * 10;
    HH += (t[1] - '0');
    mm += (t[3] - '0') * 10;
    mm += (t[4] - '0');
    SS += (t[6] - '0') * 10;
    SS += (t[7] - '0');
  }

  string toString() {
    return to_string(HH / 10)
        .append(to_string(HH % 10))
        .append(":")
        .append(to_string(mm / 10))
        .append(to_string(mm % 10))
        .append(":")
        .append(to_string(SS / 10))
        .append(to_string(SS % 10));
  }

  int operator-(const Time& T) const {
    int a = getTime(), b = T.getTime();
    return (a - b > 0) ? a - b : b - a;
  }

  /* returns seconds of this Time from 00:00:00 */
  int getTime() const { return (HH * 60 + mm) * 60 + SS; }
};

int main() {
  Time T("01:01:01");
  cout << T.toString() << endl;
  cout << T.getTime() << endl;
}