#include <iostream>
#include <vector>

using namespace std;

int faceValue(const int &face) { return (face - 1) ? (face - 1) : 12; }
int suitValue(string suit) {
  return suit == "spade" ? 4 : suit == "heart" ? 3 : suit == "diamond" ? 2 : 1;
}

// Please finish the comparison operator override
// compare face first, if the same then compare suit
// 請完成比較運算子多載
// 先比較 face ， face 一樣再比較 suit
// 1 > 13 > 12 > 11 > 10 > 9 > 8 > 7 > 6 > 5 > 4 > 3 > 2
// spade > heart > diamond > club

int main() {
  cout << faceValue(10) << endl;
  cout << suitValue("heart") << endl;
  int a = 1;
  cout << (1 == 1 || a++) << endl;
  cout << a;
}
