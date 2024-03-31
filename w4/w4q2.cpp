#include <algorithm>
#include <iostream>

using namespace std;

class Fraction {
 private:
  int numerator, denominator;

 public:
  Fraction() : numerator(0), denominator(1) {}

  Fraction(int n, int m) : numerator(n) {
    if (m == 0) throw "divided by zero";
    denominator = m;
  }

  int getNumerator() const { return numerator; }

  int getDenominator() const { return denominator; }

  void setNumerator(int n) { numerator = n; }

  void setDenominator(int m) {
    if (m == 0) throw "divided by zero";
    denominator = m;
  }

  friend std::ostream& operator<<(std::ostream& out, const Fraction& f) {
    if (f.denominator != 1)
      out << "[" << f.numerator << "/" << f.denominator << "]";
    else
      out << f.numerator;
    return out;
  }
};
//----------------------------
int LCM(int num1, int num2) { return ((num1 * num2) / __gcd(num1, num2)); }

/* reduces the fraction to irreducible fraction and return given F address for
 * sake of chain pattern*/
Fraction* reduce(Fraction* F) {
  int gcd = __gcd(F->getNumerator(), F->getDenominator());
  while (gcd != 1 && gcd) {
    F->setNumerator(F->getNumerator() / gcd);
    F->setDenominator(F->getDenominator() / gcd);
    gcd = __gcd(F->getNumerator(), F->getDenominator());
  }
  return F;
}

/* changes denominator to given target. if possible, set denominator to target
 * and retain the value of the fraction */
void changeDenominator(Fraction* F, int target) {
  reduce(F);
  if (target > F->getDenominator() && !(target % F->getDenominator())) {
    F->setNumerator(F->getNumerator() * (target / F->getDenominator()));
    F->setDenominator(target);
  }
}

Fraction operator+(Fraction& F, Fraction& G) {
  int lcm = LCM(F.getDenominator(), G.getDenominator());
  changeDenominator(&F, lcm);
  changeDenominator(&G, lcm);
  return *(reduce(new Fraction((F.getNumerator() + G.getNumerator()), lcm)));
}

Fraction operator-(Fraction& F, Fraction& G) {
  int lcm = LCM(F.getDenominator(), G.getDenominator());
  changeDenominator(&F, lcm);
  changeDenominator(&G, lcm);
  return *(reduce(new Fraction((F.getNumerator() - G.getNumerator()), lcm)));
}

bool operator==(Fraction& F, Fraction& G) {
  reduce(&F);
  reduce(&G);
  return (F.getNumerator() == 0 && G.getNumerator() == 0) ||
         (F.getNumerator() == G.getNumerator() &&
          F.getDenominator() == G.getDenominator());
}
//----------------------------------------

int main() {
  Fraction f(8, 14);
  Fraction g(5, 7);
  reduce(&f);
  reduce(&g);
  cout << f << " + " << g << " = " << (f + g) << endl;
  cout << f << " - " << g << " = " << (f - g) << endl;
  cout << f << " == " << g << " ? " << (f == g) << endl;
}