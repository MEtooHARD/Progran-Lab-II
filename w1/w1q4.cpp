#include <iostream>

using namespace std;

class WlakingMan {
 public:
  double km, hour;
  WlakingMan(double km, double hour) {
    this->km = km;
    this->hour = hour;
  }
  double velocity() { return this->km / this->hour; }
};

int main() {
  double km, hour;
  cin >> km >> hour;
  cout << (new WlakingMan(km, hour))->velocity() << endl;
}