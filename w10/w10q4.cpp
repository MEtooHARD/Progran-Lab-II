#include <iostream>

using namespace std;

bool isPrime(int n) {
  int i;
  if (n == 0 || n == 1) return false;

  for (i = 2; i <= (n / 2); i++)
    if (n % i == 0) return false;
  return true;
}

int reverse(int n) {
  int result = 0;
  while (n) {
    result = result * 10 + n % 10;
    n /= 10;
  }
  return result;
}

int main() {
  int n;
  while (cin >> n) {
    cout << n << " is "
         << (isPrime(n) ? ((isPrime(reverse(n)) && n != reverse(n)) ? ("emirp")
                                                                    : ("prime"))
                        : ("not prime"))
         << ".\n";
  }
}