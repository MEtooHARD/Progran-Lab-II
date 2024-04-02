#include <iostream>

using namespace std;

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

  };
};

int main() {
  //
}