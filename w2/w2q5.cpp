#include <iostream>
#include <math.h>
using namespace std;

class Plate {
  private:
int num=0;
  
  public:
Plate(int num): num(num) {}
bool numAtNth(int n, int place) {
return nthNum(place) == n;
}
int nthNum(int p) { return num/(int)pow(10, p-1)%10;}
};


int main() {
int num = 0;
cin >> num;
Plate plate(num);
bool has4 = false;
for(int i = 0; i < 4 && !has4; i++)
 if(plate.numAtNth(4, i+1))
    has4 = true;

cout << (has4 ? "Yes" : "No");
}
