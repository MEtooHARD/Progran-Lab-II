#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class A {
 public:
  static const int pi = 3;
  int lmao = 0;
  A(int a) : lmao(a) {}

  /* A(int a) {
    lmao = a;
    //
  } */
};

int main() {
  A a();
  //
  A::pi;
}
