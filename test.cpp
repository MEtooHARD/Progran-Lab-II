#include <iostream>

using namespace std;

class A {
 public:
  int lmao = 0;
};

int main() {
  A *a = new A();
  A b = *a;
  b.lmao++;
  cout << a->lmao << endl;
}