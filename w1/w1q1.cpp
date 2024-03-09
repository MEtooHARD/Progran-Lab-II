#include <iostream>

using namespace std;

class Point {
 public:
  float X, Y;
  Point(float x, float y) {
    this->X = x;
    this->Y = y;
  }
};

int main() {
  float count;
  cin >> count;
  for (int i = 0; i < count; i++) {
    float x, y;
    cin >> x >> y;
    Point* pt = new Point(x, y);
    cout << "(" << pt->X << ", " << pt->Y << ")" << endl;
  }
}