#include <math.h>

#include <iostream>

using namespace std;

class Point {
 public:
  double x = 0, y = 0;

  Point() {}

  Point(int x, int y) : x(x), y(y) {}

  double distanceTo(Point& p) {
    return sqrtf(pow(x - p.x, 2) + pow(y - p.y, 2));
  }

  void print() { cout << "(" << x << ", " << y << ")"; }
};

class Mountain {
  Point* spots[100];

 public:
  Mountain() {
    int amount;
    cin >> amount;
    int x, y;
    for (int i = 0; i < amount; i++) {
      cin >> x >> y;
      spots[i] = new Point(x, y);
    }
    qsort(spots, amount, sizeof(Point*), [](const void* a, const void* b) {
      return (int)((**(Point**)a).x - (**(Point**)b).x);
    });

    // for (int i = 0; i < amount; i++) {
    //   spots[i]->print();
    //   cout << endl;
    // }
    // for (int i = 0; i < amount - 1; i++)
    //   cout << spots[i]->distanceTo(*spots[i + 1]) << endl;

    // Point* current = spots[amount - 1];
    int height = 0;
    double length = 0;
    for (int i = amount - 2; i >= 0; i--) {
      if (spots[i]->y > height) {
        length += ((spots[i]->y - height) / (spots[i]->y - spots[i + 1]->y)) *
                  spots[i]->distanceTo(*spots[i + 1]);
        // spots[i + 1]->print();
        // cout << " to ";
        // spots[i]->print();
        // cout << ": "
        //      << ((spots[i]->y - height) / (spots[i]->y - spots[i + 1]->y)) *
        //             spots[i]->distanceTo(*spots[i + 1])
        //      << "\nheight: " << height << "\n"
        //      << endl;
        height = spots[i]->y;
      }
    }
    printf("%.2f\n", length);
  }
};

int main() {
  int sets;
  cin >> sets;
  for (int i = 0; i < sets; i++) {
    Mountain mount;
  }
}