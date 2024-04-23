#include <iostream>

using namespace std;

int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isOfMultiple(int i, int m) { return !(i % m); }
bool is_leapyear(int y) {
  return (y % 4 == 0) && !(y % 100 == 0) || (y % 400 == 0);
}

class Date {
  int YYYY = 0, MM = 0, DD = 0;

 public:
  Date() : YYYY(1900), MM(1), DD(1){};

  Date(string s) { sscanf(s.c_str(), "%d/%d/%d", &YYYY, &MM, &DD); };

  string toString() const {
    char result[11];
    sprintf(result, "%04d/%02d/%02d", YYYY, MM, DD);
    return result;
  };

  int operator-(const Date& D) const { return abs(getDay() - D.getDay()); };

  int getDay() const {
    int days = (YYYY - 1900) * 365 + DD - 1;
    for (int i = 1900; i < YYYY; i += 4)
      if (is_leapyear(i)) days++;

    for (int i = 1; i < MM; i++) days += Date::DaysOfMonth(i);

    if (is_leapyear(YYYY) && MM > 2) days++;

    return days;
  }

  static const int DaysOfMonth(int m) { return months[m - 1]; }
};

int main() {
  string a, b;
  cin >> a >> b;
  Date c(a), d(b);
  cout << (c - d) << endl;
}