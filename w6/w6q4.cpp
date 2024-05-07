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

  bool operator!=(const Point &p) { return x != p.x || y != p.y; }
};

class Segment {
  Point p1, p2;

 public:
  Segment() {}
  Segment(const Point &p1, const Point &p2) : p1(p1), p2(p2) {}

  Point getStart() { return p1; }
  Point getEnd() { return p2; }
  float getLength() { return p1.getDistance(p2); }
};

class Shape {
 public:
  Shape() {}
  Shape(Segment *segs, int count) {
    // if (count < 3) throw invalid_argument("segs not enough");
    if (segs[0].getStart() != segs[edgeCount - 1].getEnd())
      throw std::invalid_argument("Segments do not form a closed path");
    //
  }

  virtual float getArea() = 0;

  float getPerimeter();

  Segment &getSeg(int index) { return seg[index]; }

 private:
  Segment seg[10];
  int edgeCount = 0;
};