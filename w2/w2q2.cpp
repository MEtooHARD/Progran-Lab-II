#include <math.h>

#include <iostream>

using namespace std;

class Point {
 public:
  Point(double _x, double _y){};
  double getX();
  double getY();

 private:
  double x, y;
};

class Segment {
 public:
  Point *p1, *p2;
  Segment(Point *p1, Point *p2) {
    this->p1 = p1;
    this->p2 = p2;
  };
  double length() {
    return sqrt(pow(this->p1->getX() - this->p2->getX(), 2) +
                pow(this->p1->getY() - this->p2->getY(), 2));
  }
  Point getEnd(int n) { return n == 0 ? *(this->p1) : *(this->p2); }
};