#include <iostream>

using namespace std;

class Digit {  // class Digit represent a digit in base 10
  int digit = 0;

 public:
  Digit(int d) : digit(d % 10){};
  Digit(){};
  void setDigit(int d) { digit = d % 10; }
  int getDigit() const { return digit; }
};

class Integer {  // class Integer represent a poistive integer
  Digit value[1000];
  int digits = 0;

 public:
  Integer(string n) {
    int arrow = 0;
    while (n[arrow] >= '0' && n[arrow] < '9') {
      value[arrow] = *(new Digit(n[arrow] - '0'));
      arrow++;
    }
    digits = arrow + 1;
  };
  Integer() {
    value[0] = *(new Digit(0));
    digits = 1;
  };
  void displayInBase(int base) const {
    for (int i = 0; i < digits - 1; i++) {
      cout << value[i].getDigit();
    }
  };
};

int main() {
  string in;
  int j;
  cin >> in;
  Integer i(in);
  /* for (j = 2; j <= 16; j++) {
    i.displayInBase(j);
    cout << endl;
  } */
  i.displayInBase(10);
}
