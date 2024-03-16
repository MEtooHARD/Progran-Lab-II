#include <math.h>

#include <iostream>

using namespace std;

class Point {
 public:
  int x, y;
  Point(double _x, double _y) {
    x = _x;
    y = _y;
  };
  double getX() { return x; };
  double getY() { return y; };
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

int *joinedSegs;

class Path {
 private:
  double len = 0;
  Segment *headSeg, *tailSeg, *segs;
  int amount;

 public:
  Path(Segment *incomingSegs, int amount) : segs(incomingSegs), amount(amount) {
    joinedSegs = (int *)malloc(sizeof(int *) * amount);
    headSeg = &(incomingSegs[0]);
    tailSeg = &(incomingSegs[0]);

    for (int i = 0; i < amount; i++) {
      int next = nextJoinableSeg();
      if (next) {
        len += segs[next].length();
        joinedSegs[next] = 1;
        (joinable(headSeg, &segs[next]) ? headSeg : tailSeg) = &segs[next];
      }
    }

    int c = 0;
    for (; c < amount; c++)
      ;
    if (c == amount && !joinable(headSeg, tailSeg))
      cout << len;
    else
      cout << "-1";
  }

  // returns -1 if no seg joinable
  int nextJoinableSeg() {
    int i = amount - 1;
    for (; i >= 0; i--) {
      if (joinedSegs[i]) continue;
      if (joinable(headSeg, &segs[i]) || joinable(tailSeg, &segs[i])) break;
    }
    return i;
  }

  bool joinable(Segment *seg1, Segment *seg2) {
    return pointOverlap((seg1->getEnd(0)), (seg2->getEnd(0))) ||
           pointOverlap((seg1->getEnd(1)), (seg2->getEnd(0))) ||
           pointOverlap((seg1->getEnd(1)), (seg2->getEnd(1))) ||
           pointOverlap((seg1->getEnd(0)), (seg2->getEnd(1)));
  }
};