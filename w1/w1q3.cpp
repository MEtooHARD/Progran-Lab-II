#include <math.h>

#include <iostream>

using namespace std;

class Point {
 public:
  double X = 0, Y = 0;
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
  Point *P1 = new Point(), *P2 = new Point();

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

class Triangle {
 public:
  Triangle(Point *a, Point *b, Point *c) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->ab = new Segment(a, b);
    this->bc = new Segment(b, c);
    this->ac = new Segment(a, c);
  }
  Point *a, *b, *c;
  Segment *ab, *bc, *ac;
  double perimeter() {
    return this->ab->length() + this->bc->length() + this->ac->length();
  }
};

int main() {
  int amount;
  cin >> amount;
  double x1, y1, x2, y2, x3, y3;
  Triangle *tng;
  Point *a = new Point(), *b = new Point(), *c = new Point();
  for (int i = 0; i < amount; i++) {
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    a->setX(x1);
    a->setY(y1);
    b->setX(x2);
    b->setY(y2);
    c->setX(x3);
    c->setY(y3);
    cout << (new Triangle(a, b, c))->perimeter() << endl;
  }

  return 0;
}