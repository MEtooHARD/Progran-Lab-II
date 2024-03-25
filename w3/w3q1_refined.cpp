#include <iostream>

using namespace std;

class Digit {  // class Digit represent a digit in base 10
  int digit = 0;

 public:
  Digit(int d) : digit(d){};
  Digit(){};
  void setDigit(int d) { digit = d; }
  int getDigit() const { return digit; }
  /* supports at highest base 16 otherwise it could bee anti-human to read*/
  char getChar() { return digit < 10 ? ('0' + digit) : ('A' + digit - 10); }
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
  /* the number's ones digit will be at value[x], x >= 0 */
  Integer(string n) {
    int arrow = 0;
    while (n[arrow] >= '0' && n[arrow] <= '9') addDigit(n[arrow++] - '0');
  };

  /* default: 0 digits */
  Integer() { value[0] = *(new Digit(0)); }

  /* get digits */
  int getDigits() { return digits; }

  /* get specified digit. count from 0 */
  Digit digit(int digit) { return value[digit]; }

  /* add a digit at the very last of the array and increase digits by 1 */
  void addDigit(int num) { value[digits++] = *(new Digit(num)); }

  /* insert a digit at the start of the Integer(highest digit) and increase
   * digits by 1 */
  void insertDigit(int num) {
    displace(1);
    setDigit(0, num);
  }

  /* display all counted digits */
  void displayAll() {
    for (int i = 0; i < digits; i++) cout << digit(i).getChar();
  }

  /* displays the converted Integer */
  void displayInBase(int base) { convertToBase(base).displayAll(); };

  /* converts the Integer into dedicated base */
  Integer convertToBase(int base) {
    Integer converted, remainder = *this;
    do {
      DivisionResult result = remainder.divideBy(base);
      converted.insertDigit(result.remainder);
      remainder = *(result.quotient);
    } while (remainder.digit(0).getDigit());

    return converted;
  }

  /* divides with given dividor and return quotient and remainder */
  DivisionResult divideBy(int dividor) {
    int remainder = digit(0).getDigit(), idx = 0;
    Integer quotient;

    while (remainder < dividor && idx < digits - 1)
      remainder = remainder * 10 + digit(++idx).getDigit();
    while (idx < digits) {
      quotient.addDigit(remainder / dividor);
      remainder %= dividor;
      remainder = remainder * 10 + digit(++idx).getDigit();
    }
    remainder /= 10;

    return *(new DivisionResult(&quotient, remainder));
  }

  /* sets specified digit with given number */
  void setDigit(int digit, int num) { value[digit].setDigit(num); }

  /* displaces all digits by either positive and negative volume.
   * will also fill new created digits or deprecated digits with 0s */
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