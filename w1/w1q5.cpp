#include <iostream>
#define boolean bool
using namespace std;

class Segment {
 public:
  double a, b;
  Segment(double a, double b) {
    if (a < b) {
      this->a = a;
      this->b = b;
    } else {
      this->b = a;
      this->a = b;
    }
  }
  boolean overlayWith(Segment *segment) {
    return !((this->b <= segment->a) || (this->a >= segment->b));
  }
};

int main() {
  double a1, b1, a2, b2;
  cin >> a1 >> b1 >> a2 >> b2;
  Segment *s1 = new Segment(a1, b1);
  Segment *s2 = new Segment(a2, b2);
  cout << (s1->overlayWith(s2) ? "" : "no ") << "overlay";
}