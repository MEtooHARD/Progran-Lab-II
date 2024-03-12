#include <iostream>

using namespace std;

class Point {
 private:
  float X = 0, Y = 0;

 public:
  Point(float x, float y) {
    this->X = x;
    this->Y = y;
  }
  float getX() { return this->X; };
  float getY() { return this->Y; };
};

int main() {
  int N;
  cin >> N;
  Point *p;
  float x, y;
  for (int i = 0; i < N; i++) {
    cin >> x >> y;
    p = new Point(x, y);
    cout << "(" << p->getX() << ", " << p->getY() << ")" << endl;
  }
}