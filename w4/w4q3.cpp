#include <algorithm>
#include <iostream>

using namespace std;

class Fraction;

Fraction* reduce(Fraction* F);

class Fraction {
 private:
  int numerator, denominator;

 public:
  Fraction() : numerator(0), denominator(1) {}

  Fraction(int n, int m) : numerator(n) {
    if (m == 0) throw "divided by zero";
    denominator = m;
    reduce(this);
  }

  int getNumerator() const { return numerator; }

  int getDenominator() const { return denominator; }

  void setNumerator(int n) { numerator = n; }

  void setDenominator(int m) {
    if (m == 0) throw "divided by zero";
    denominator = m;
  }

  void display() {
    reduce(this);
    cout << *this;
  }

  friend std::ostream& operator<<(std::ostream& out, const Fraction& f) {
    if (f.denominator != 1)
      out << "(" << f.numerator << "/" << f.denominator << ")" << endl;
    else
      out << '(' << f.numerator << ')';
    return out;
  }

  void operator=(Fraction F) {
    numerator = F.getNumerator();
    denominator = F.getDenominator();
  }
};

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
  if (F->getDenominator() < 0 && F->getNumerator() > 0) {
    F->setDenominator(-F->getDenominator());
    F->setNumerator(-F->getNumerator());
  } else if (F->getNumerator() < 0 && F->getDenominator() < 0) {
    F->setNumerator(-F->getNumerator());
    F->setDenominator(-F->getDenominator());
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

/* make the given two fractions common fractions and return the used denominator
 * a.k.a. the lcm of the denominators of the two given fraction */
int common_ize(Fraction* F, Fraction* G) {
  int lcm = LCM(F->getDenominator(), G->getDenominator());
  changeDenominator(F, lcm);
  changeDenominator(G, lcm);
  return lcm;
}

Fraction operator+(Fraction F, Fraction G) {
  common_ize(&F, &G);
  return *(reduce(
      new Fraction((F.getNumerator() + G.getNumerator()), F.getDenominator())));
}

Fraction operator-(Fraction F, Fraction G) {
  common_ize(&F, &G);
  return *(reduce(
      new Fraction((F.getNumerator() - G.getNumerator()), F.getDenominator())));
}

Fraction operator*(Fraction F, Fraction G) {
  return *(reduce(new Fraction(F.getNumerator() * G.getNumerator(),
                               F.getDenominator() * G.getDenominator())));
}

Fraction operator/(Fraction F, Fraction G) {
  return *(reduce(new Fraction((F.getNumerator() * G.getDenominator()),
                               F.getDenominator() * G.getNumerator())));
}

Fraction operator!(Fraction F) {
  return *(new Fraction(F.getDenominator(), F.getNumerator()));
}

bool operator==(Fraction F, Fraction G) {
  reduce(&F);
  reduce(&G);
  return (F.getNumerator() == 0 && G.getNumerator() == 0) ||
         (F.getNumerator() == G.getNumerator() &&
          F.getDenominator() == G.getDenominator());
}

int main() {
  Fraction a(1, -2), b(1, 2), c, d, e, f;
  //   a = (((b + c) - d) * e)  / f;
  cout << a;
  a = a * b;
  cout << !a;
}