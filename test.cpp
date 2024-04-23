#include <iostream>

using namespace std;

class Dick {
  void cum() {}

  ~Dick() {
    for (int i = 0; i < 999999999; i++) cum();
  }
};

class A {
 public:
  virtual void foo() {}
};

class B : public A {
 public:
  B() {
    foo(0);
    A::foo();
  }
  void foo(int i) {}
};

int main() { A a; }
