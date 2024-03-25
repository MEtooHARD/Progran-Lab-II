#include <iostream>

using namespace std;

class Digit {  // class Digit represent a digit in base 10
  int digit;

 public:
  Digit(int d) : digit(d) {}
  Digit() { digit = 0; }
  void setDigit(int d) { digit = d; }
  int getDigit() const { return digit; }
  char getChar() { return digit < 10 ? ('0' + digit) : ('A' + digit - 10); }
};

class Integer {  // class Integer represent a integer
  Digit value[1000];
  bool sign;
  int digits = 0;

 public:
  // default constructor will construct an Integer object with value 0.
  Integer(){};

  // construct an integer in base 10 using a string.
  // This constructor will convert the given string to integer if possible.
  // Otherwise it will convert the digit part in prefix of the given string.
  Integer(string n) {  // the number's ones digit will be at value[x], x >= 0
    int arrow = 0;
    while (n[arrow] >= '0' && n[arrow] <= '9') addDigit(n[arrow++] - '0');
  };

  /* add a digit at the very last of the array and increase digits by 1 */
  void addDigit(int num) { value[digits++] = *(new Digit(num)); }

  // function addition will add up two integer and return a new Integer object
  // as result.
  Integer addition(Integer &b) {
    int remainder = 0, idx = 0;
    Integer result;
    while (b.digits >= ++idx || this->digits >= idx) {
      /* if the digit is available, add them together*/
      if (b.digits >= idx) remainder += b.digit(b.digits - idx).getDigit();
      if (this->digits >= idx)
        remainder += this->digit(this->digits - idx).getDigit();
      result.insertDigit(remainder % 10);
      remainder /= 10;
    }
    if (remainder) result.insertDigit(remainder);

    return result;
  };

  // function subtraction will minus b from current object and return a new as
  // result.
  Integer subtraction(Integer &b) {
    int minuend = 0, subtrahend = 0, idx = 0,
        digitsDiff = b.digits - this->digits;
    // while () {
    // }
  };

  void setDigit(int digit, int num) { value[digit].setDigit(num); }

  void manipulateDigit(int digit, int value) {
    int remainder = this->digit(digit).getDigit() + value;
    while (digit > digits) insertDigit(0);
    do {
      setDigit(digit--, remainder % 10);
      remainder /= 10;
    } while (remainder);

    //
  };

  Digit digit(int digit) { return value[digit]; }

  void insertDigit(int num) {
    displace(1);
    setDigit(0, num);
  }

  void display() {
    for (int i = 0; i < digits; i++) cout << digit(i).getChar();
  };

  /* passed */
  void displace(int volume) {
    if (volume > 0) {
      for (int idx = digits + volume - 1; idx >= 0; idx--)
        setDigit(idx, digit(idx - volume).getDigit());
      for (int i = 0; i < volume; i++) setDigit(i, 0);
    } else if (volume < 0) {
      for (int idx = 0; idx < digits + volume - 1; idx++)
        setDigit(idx, digit(idx - volume).getDigit());
      for (int i = digits - 1; i >= digits + volume; i--) setDigit(i, 0);
    }
    digits += volume;
  }
};

int main() {
  string a, b;
  cin >> a >> b;
  Integer num1(a), num2(b);
  // num1.addition(num2).display();
  // cout << endl;
  // num2.addition(num1).display();
  // cout << endl;
  // num1.subtraction(num2).display();
  // cout << endl;
  // num2.subtraction(num1).display();
  // cout << endl;
}