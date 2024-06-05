#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class Date {
 public:
  bool is_leapyear() {
    return (((y % 4 == 0) && !(y % 100 == 0)) || (y % 400 == 0));
  }

  Date(int x) : y(x / 10000), m(x % 10000 / 100), d(x % 100), code(x) {}

  bool operator==(Date &d2) { return (code == d2.code); }

  int prevDay() {
    int yy = y, mm = m, dd = d;
    m_days[1] = 28;
    if (is_leapyear()) {
      m_days[1] = 29;
    }
    if (mm == 1 && dd == 1) {
      yy--;
      mm = 12;
      dd = 31;
    } else {
      dd--;
      if (dd < 1) {
        mm--;
        dd = m_days[mm - 1];
      }
    }
    return yy * 10000 + mm * 100 + dd;
  }

  int nextDay() {
    int yy = y, mm = m, dd = d + 1;
    m_days[1] = 28;
    if (is_leapyear()) {
      m_days[1] = 29;
    }
    if (dd > m_days[mm - 1]) {
      dd = 1;
      mm++;
    }
    if (mm == 13) {
      mm = 1;
      yy++;
    }
    return yy * 10000 + mm * 100 + dd;
  }

  string toString() {
    return to_string(m) + "/" + to_string(d) + "/" + to_string(y);
  }

  int getcode() { return code; }

 private:
  int y = 0, m = 0, d = 0, code = 0, totaldays = 0;
  int m_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};
class DateRange {
 public:
  Date start, end;
  DateRange(int d1, int d2) : start(Date(d1)), end(Date(d2)) {}
  Date get_start() { return start; }
  Date get_end() { return end; }
  string print() {
    if (start == end) {
      return start.toString();
    }
    return start.toString() + " to " + end.toString();
  }
};

ostream &operator<<(ostream &os, DateRange &range) {
  os << range.print();
  return os;
}

map<int, int> t;
class Quotesmanager {
 public:
  void record(Date d) {
    t[d.getcode()] = 0;
    t[d.nextDay()] = 0;
    t[d.prevDay()] = 0;
  }

  Quotesmanager(int n, int m) : nx(n), nr(m) {
    t.clear();
    int d1, d2;
    for (int i = 0; i < nx; i++) {
      cin >> d1 >> d2;
      exist.push_back(DateRange(d1, d2));
      record(exist[i].start);
      record(exist[i].end);
    }
    for (int i = 0; i < nr; i++) {
      cin >> d1 >> d2;
      incoming.push_back(DateRange(d1, d2));
      record(incoming[i].start);
      record(incoming[i].end);
    }
  }

  ~Quotesmanager() {
    exist.clear();
    incoming.clear();
  }

  void date_R() {
    for (map<int, int>::iterator it = t.begin(); it != t.end(); it++) {
      it->second = size++;
      date.push_back(it->first);
    }
  }

  void show_result() {
    date_R();
    vector<int> mark(size, 0);
    int l, r, has = 0;
    for (int i = 0; i < nr; i++) {
      l = t[incoming[i].start.getcode()];
      r = t[incoming[i].end.getcode()];
      for (int j = l; j <= r; j++) mark[j] = 1;
    }
    for (int i = 0; i < nx; i++) {
      l = t[exist[i].start.getcode()];
      r = t[exist[i].end.getcode()];
      for (int j = l; j <= r; j++) mark[j] = 0;
    }
    for (int i = 0; i < mark.size(); i++) {
      if (mark[i] == 1) {
        has = 1;
        start = i;
        if (i + 1 < mark.size() && mark[i + 1] == 1)
          while (i + 1 < mark.size() && mark[i + 1] == 1) i++;

        end = i;
        out.push_back(DateRange(date[start], date[end]));
      }
    }
    if (!has)
      cout << "No additional quotes are required.\n";
    else
      for (int i = 0; i < out.size(); i++) {
        // cout << "    ";
        cout << out[i] << endl;
      }
  }

 private:
  int nx, nr, size = 0, start, end;
  vector<DateRange> exist, incoming, out;
  vector<int> date;
};

int main() {
  int cases = 1;
  Quotesmanager *q = NULL;
  int n, m;
  while (cin >> n >> m) {
    if (n == 0 && m == 0) {
      return 0;
    }
    q = new Quotesmanager(n, m);
    cout << "Case " << cases++ << ":\n";
    q->show_result();
    delete q;
  }
}
