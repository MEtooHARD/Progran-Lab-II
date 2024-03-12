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
  Segment *segs;
  int amount;
  Path(Segment *segs, int amount) {
    this->segs = segs;
    this->amount = amount;
    double length = 0;
    bool connected = true;
    int nowChecking = 0;
    while (connected && nowChecking < amount) {
      nowChecking++;
      int lastConnectedPoint;
      for (int i = 0; i < amount; i++) {
        if (i == nowChecking) continue;
        if (0) {
        } else {
          connected = false;
          break;
        }
      }
    }
  }
};

bool pointOverlap(Point p1, Point p2) {
  return p1.getX() == p2.getX() && p1.getY() == p2.getY();
}