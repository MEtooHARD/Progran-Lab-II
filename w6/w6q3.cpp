#include <math.h>

#include <iostream>

using namespace std;

class Point {
  float x = 0, y = 0;

 public:
  Point() {}
  Point(float x, float y) : x(x), y(y) {}

  void printPoint() const { cout << '(' << x << ", " << y << ')'; }

  float getX() { return x; }
  float getY() { return y; }

  void setX(float n) { x = n; }
  void setY(float n) { y = n; }

  float getDistance(Point &p) {
    return sqrtf(pow(x - p.x, 2) + pow(y - p.y, 2));
  }
};

class Segment {
  Point p1, p2;

 public:
  Segment() {}
  Segment(const Point &p1, const Point &p2) : p1(p1), p2(p2) {}

  float getLength() { return p1.getDistance(p2); }
};

/* int main() {
  Point a, b(5, 12);
  //   a.printPoint();
  //   b.printPoint();
  Segment seg(b, a);
  cout << seg.getLength() << endl;
} */