#include <math.h>

#include <iostream>

using namespace std;

class Point {
 public:
  Point(double _x, double _y);
  double getX();
  double getY();
};

class Segment {
 public:
  Segment(Point p1, Point p2);
  Point getEnd(int n);
  double length();
};

class Path {
 public:
  Segment *connectedSegs;
  int amount;
  Path(Segment *incomingSegs, int amount) {
    connectedSegs = (Segment *)malloc(sizeof(Segment *) * amount);
    this->amount = amount;
    double length = 0;
    bool connection = true;
    int nowChecking = 0, head = 0, tail = 0, headEnd, tailEnd;
    while (connection && nowChecking < amount) {
      nowChecking++;

      for (int i = 1; i < amount; i++) {
        Segment now = incomingSegs[i];

        if (0) {
        }
      }
    }
  }
};

bool pointOverlap(Point p1, Point p2) {
  return p1.getX() == p2.getX() && p1.getY() == p2.getY();
}

bool validConnection(Segment seg1, Segment seg2, int seg1End, int seg2End) {
  return seg1.getEnd(seg1End).getX() == seg2.getEnd(seg2End).getX();
}