#include <math.h>

#include <iostream>

using namespace std;

class Point {
 public:
  double X, Y;
  /* Point(float x, float y) {
    this->X = x;
    this->Y = y;
  } */
  void setX(double n) { this->X = n; }
  void setY(double n) { this->Y = n; }
  double getX() { return this->X; }
  double getY() { return this->Y; }
};

class Segment {
 private:
  Point *P1, *P2;

 public:
  Segment(Point *p1, Point *p2) {
    this->P1 = p1;
    this->P2 = p2;
  }
  double length() {
    return sqrt(pow(this->P1->getX() - this->P2->getX(), 2) +
                pow(this->P1->getY() - this->P2->getY(), 2));
  }
};

int main() {
  int amount;
  cin >> amount;
  double x1, y1, x2, y2;
  Point *p1 = new Point(), *p2 = new Point();
  Segment *segment = new Segment(p1, p2);
  for (int i = 0; i < amount; i++) {
    cin >> x1 >> y1 >> x2 >> y2;
    p1->setX(x1);
    p1->setY(y1);
    p2->setX(x2);
    p2->setY(y2);
    cout << segment->length() << endl;
  }
}