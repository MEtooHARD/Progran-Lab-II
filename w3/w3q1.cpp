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

class Integer;

class DivisionResult {
 public:
  int remainder;
  Integer *quotient;
  DivisionResult(Integer *quotient, int remainder)
      : quotient(quotient), remainder(remainder) {}
};

class Integer {  // class Integer represent a poistive integer
 private:
  Digit value[1000];
  int digits = 0;

 public:
  Integer(string n) {  // the number's ones digit will be at value[x], x >= 0
    int arrow = 0;
    while (n[arrow] >= '0' && n[arrow] < '9') addDigit(n[arrow++] - '0');
  };

  Integer() { value[0] = *(new Digit(0)); }

  int getDigits() { return digits; }

  Digit digit(int digit) { return value[digit]; }

  /* add a digit at the very last of the array and increase digits by 1 */
  void addDigit(int num) { value[digits++] = *(new Digit(num)); }

  /* insert a digit at the start of the Integer(highest digit) and increase
   * digits by 1 */
  void insertDigit(int num) {
    for (int i = digits++; i >= 1; i--) value[i] = value[i - 1];
    value[0] = *(new Digit(num));
  }

  void displayAll() {
    for (int i = 0; i < digits; i++) cout << digitChar(i);
  }

  Integer convertToBase(int base) {
    Integer converted, remainder = *this;
    cout << "-----------------------------------" << endl;
    do {
      DivisionResult result = remainder.divideBy(base);
      converted.insertDigit(result.remainder);
      remainder = *(result.quotient);
      cout << "---------------" << endl;
    } while (remainder.digit(0).getDigit());

    return converted;
  }

  void displayInBase(int base) { convertToBase(base).displayAll(); };

  DivisionResult divideBy(int dividor) {
    int remainder = digit(0).getDigit(), idx = 0;
    Integer quotient;

    while (remainder < dividor && idx < digits - 1)
      remainder = remainder * 10 + digit(++idx).getDigit();
    cout << "dividend: ";
    displayAll();
    cout << "\ndividor: " << dividor << endl;
    // cout << "remainder: " << remainder << endl;
    while (idx < digits) {
      cout << "remainder: " << remainder << endl;
      quotient.addDigit(remainder / dividor);
      remainder %= dividor;
      remainder = remainder * 10 + digit(++idx).getDigit();
      cout << "quotient: ";
      quotient.displayAll();
      cout << endl;
    }
    remainder /= 10;

    return *(new DivisionResult(&quotient, remainder));
  }

  char digitChar(int digit) {
    return this->digit(digit).getDigit() < 9
               ? ('0' + this->digit(digit).getDigit())
               : ('A' + this->digit(digit).getDigit() - 10);
  }
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
  DivisionResult result = i.divideBy(16);
  result.quotient->displayAll();
}
