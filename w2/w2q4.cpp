#include <math.h>

#include <iostream>

using namespace std;

class TWT {  // TollWayToll (大噓)
 public:
  int distance;
  TWT(int distance) { this->distance = distance; }
  int toll() {
    return round(distance < 200 ? distance * 1.2
                                : 200 * 1.2 + ((distance / 200 - 1) * 200 +
                                               distance % 200) *
                                                  (1.2 * 0.75));
  }
};

int main() {
  int distance;
  cin >> distance;
  cout << (new TWT(distance))->toll();
}
