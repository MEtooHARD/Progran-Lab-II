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

bool pointOverlap(Point p1, Point p2) {
  return p1.getX() == p2.getX() && p1.getY() == p2.getY();
}

class Segment {
  Point p1, p2;

 public:
  Segment() {}
  Segment(const Point &p1, const Point &p2) : p1(p1), p2(p2) {}

  Point getEnd(int n) { return n ? p2 : p1; }
  float getLength() { return p1.getDistance(p2); }
};

class Shape {
 public:
  Shape() {}
  Shape(Segment *segs, int count) {
    for (int i = 0; i < count; i++) seg[i] = segs[i];
    double len = segs[0].getLength();
    if (!pointOverlap(segs[0].getEnd(0), segs[count - 1].getEnd(1))) {
      throw invalid_argument("1");
      return;
    }
    for (int i = 0; i < count - 1; i++)
      if (pointOverlap(segs[i].getEnd(1), segs[i + 1].getEnd(0)))
        len += segs[i + 1].getLength();
      else {
        throw invalid_argument("2");
        return;
      }
    edgeCount = count;
    this->len = len;
  }

  virtual float getArea() = 0;

  float getPerimeter() { return len; };

  Segment &getSeg(int index) { return seg[index]; }

 private:
  Segment seg[10];
  int edgeCount = 0;

 protected:
  double len = 0;
};

class Rectangle : public Shape {
 public:
  Rectangle(Segment *segs) : Shape(segs, 4) {}

  float getArea() override {
    return getSeg(0).getLength() * getSeg(1).getLength();
  }
};