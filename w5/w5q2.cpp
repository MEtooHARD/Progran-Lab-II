#include <iostream>

using namespace std;

int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isOfMultiple(int i, int m) { return !(i % m); }

class Date {
  int YYYY = 0, MM = 0, DD = 0;

 public:
  Date() : YYYY(1900), MM(1), DD(1){};

  Date(string s) {
    YYYY += (s[0] - '0') * 1000;
    YYYY += (s[1] - '0') * 100;
    YYYY += (s[2] - '0') * 10;
    YYYY += (s[3] - '0');

    MM += (s[5] - '0') * 10;
    MM += (s[6] - '0');

    DD += (s[8] - '0') * 10;
    DD += (s[9] - '0');
  };

  int getYear() { return YYYY; }
  int getMonth() { return MM; }
  int getDate() { return DD; }

  string toString() const {
    return to_string(YYYY / 1000)
        .append(
            to_string(YYYY / 100 % 10)
                .append(to_string(YYYY / 10 % 10).append(to_string(YYYY % 10))))
        .append("/")
        .append(to_string(MM / 10).append(to_string(MM % 10)))
        .append("/")
        .append(to_string(DD / 10).append(to_string(DD % 10)));
  };

  int operator-(const Date& D) const {
    int diff = getDay() - D.getDay();
    return diff < 0 ? -diff : diff;
  };

  int getDay() const {
    int days = -1;
    for (int i = 1900; i < YYYY; i += 4)
      if (!isOfMultiple(i, 100) || isOfMultiple(i, 400)) days++;
    days += (YYYY - 1900) * 365;

    for (int i = 1; i < MM; i++) days += Date::DaysOfMonth(i);

    days += DD;

    if (isOfMultiple(YYYY, 4) && !isOfMultiple(YYYY, 100) ||
        isOfMultiple(YYYY, 400) && MM >= 2)
      days++;

    return days;
  }

  static const int DaysOfMonth(int m) { return months[m - 1]; }
};

int main() {
  Date c("1900/01/02"), d("1900/02/01");
  cout << (c - d) << endl;
}