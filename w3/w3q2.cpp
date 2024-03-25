#include <iostream>

using namespace std;

class Digit {
  int digit = 0;

 public:
  Digit(int d) : digit(d) {}
  Digit() {}
  void add(int num) { setDigit(digit + num); }
  void setDigit(int d) { digit = d; }
  int getValue() const { return digit; }
  char getChar() { return digit < 10 ? ('0' + digit) : ('A' + digit - 10); }
};

class Integer {
  Digit value[1000];
  bool sign = true;
  int digits = 0;

 public:
  Integer(){};

  Integer(string n) {
    int arrow = 0;
    while (n[arrow] >= '0' && n[arrow] <= '9') appendDigit(n[arrow++] - '0');
  };

  /* sets the sign as true(positive) or false(negative) */
  void setSign(bool sign) { this->sign = sign; }

  /* toggles the sign from true to false or from false to true */
  void toggleSign() { setSign(!sign); }

  /* adds a digit at the very last of the array and increase digits by 1 */
  void appendDigit(int num) { value[digits++] = *(new Digit(num)); }

  /* returns an Integer that is equal to the sum of this Integer and the given b
   * Integer */
  Integer addition(Integer &b) {
    int remainder = 0, idx = 0;
    Integer result;
    while (b.digits >= ++idx || this->digits >= idx) {
      /* if the digit is available, add them together*/
      if (b.digits >= idx) remainder += b.digit(b.digits - idx).getValue();
      if (this->digits >= idx)
        remainder += this->digit(this->digits - idx).getValue();
      result.insertDigit(remainder % 10);
      remainder /= 10;
    }
    if (remainder) result.insertDigit(remainder);

    return result;
  };

  /* returns an Integer that is the result of subtraction of this Integer and
   * the given b Integer */
  Integer subtraction(Integer &b) {
    Integer subtrahend, minuend, result;
    if (largerThan(b)) {
      subtrahend = b;
      minuend = *this;
      subtrahend.displace(minuend.digits - subtrahend.digits);
    } else {
      subtrahend = *this;
      minuend = b;
      subtrahend.displace(minuend.digits - subtrahend.digits);
      result.toggleSign();
    }

    int diff = 0, carry = 0;
    for (int i = subtrahend.digits - 1; i >= 0; i--) {
      diff += (minuend.digit(i).getValue() - subtrahend.digit(i).getValue()) -
              carry;
      if (diff < 0) {
        diff += 10;
        carry = 1;
      } else
        carry = 0;

      result.insertDigit(diff % 10);
      diff /= 10;
    }
    result.trimMeanninglessZeros();

    return result;
  };

  /* removes continuous zeros all the way from the hight digit of this Integer
   */
  void trimMeanninglessZeros() {
    while (!digit(0).getValue() && digits > 1) displace(-1);
  }

  /* sets the value of the specified digit */
  void setDigit(int digit, int num) { value[digit].setDigit(num); }

  /* get Digit of given digit */
  Digit digit(int digit) { return value[digit]; }

  /* returns true only when this Integer is larger than the given b Integer */
  bool largerThan(Integer b) {
    if (b.digits < digits) return true;
    if (digits < b.digits) return false;

    for (int i = 0; i < digits; i++)
      if (digit(i).getValue() > b.digit(i).getValue())
        return true;
      else if (digit(i).getValue() < b.digit(i).getValue())
        return false;

    return false;
  }

  /* insert a digit at the start of the Integer(highest digit) and increase
   * digits by 1 */
  void insertDigit(int num) {
    displace(1);
    setDigit(0, num);
  }

  /* display all counted digits */
  void display() {
    if (!sign && (digits > 1 || (digits == 1 && digit(0).getValue() != 0)))
      cout << '-';
    for (int i = 0; i < digits; i++) cout << digit(i).getChar();
  };

  /* passed */
  void displace(int volume) {
    if (volume > 0) {
      for (int idx = digits + volume - 1; idx >= 0; idx--)
        setDigit(idx, digit(idx - volume).getValue());
      for (int i = 0; i < volume; i++) setDigit(i, 0);
    } else if (volume < 0) {
      for (int idx = 0; idx < digits + volume - 1; idx++)
        setDigit(idx, digit(idx - volume).getValue());
      for (int i = digits - 1; i >= digits + volume; i--) setDigit(i, 0);
    }
    digits += volume;
  }
};

int main() {
  // string a, b;
  // cin >> a >> b;
  // Integer num1(a), num2(b);
  // // num1.addition(num2).display();
  // // cout << endl;
  // // num2.addition(num1).display();
  // // cout << endl;
  // num1.subtraction(num2).display();
  // cout << endl;
  // num2.subtraction(num1).display();
  // cout << endl;
}