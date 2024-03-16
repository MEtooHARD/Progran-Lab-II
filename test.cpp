#include <iostream>

using namespace std;

bool truee(int *a) {
  (*a)++;
  return 1;
}

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int main() {
  int c = 3, d = 5;
  swap(&c, &d);
  cout << c << "\n" << d;
}
