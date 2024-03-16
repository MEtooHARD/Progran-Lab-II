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

bool pointOverlap(Point p1, Point p2) {
  return p1.getX() == p2.getX() && p1.getY() == p2.getY();
}

class Path {
 public:
  double len = 0;
  Path(Segment *a, int l) : len(a[0].length()) {
    int i;
    if (pointOverlap(a[0].getEnd(0), a[l - 1].getEnd(1))) {
      cout << "-1";
      return;
    }
    for (i = 0; i < l - 1; i++)
      if (pointOverlap(a[i].getEnd(1), a[i + 1].getEnd(0)))
        len += a[i + 1].length();
      else {
        cout << "-1";
        return;
      }

    cout << len;
  }
};