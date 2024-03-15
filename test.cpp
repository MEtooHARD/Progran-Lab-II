#include <iostream>

using namespace std;

class A1 {
 public:
  int a = 0;
  void adda() { this->a++; }
};

void ttt(A1 a1) { a1.adda(); }

void tttttt(A1 *a1) { a1->adda(); }

int main() {
  A1 a1;
  cout << a1.a;

  ttt(a1);
  cout << a1.a;

  tttttt(&a1);
  cout << a1.a;
}