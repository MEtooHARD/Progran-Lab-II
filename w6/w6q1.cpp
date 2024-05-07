#include <iostream>
#include <string>

using namespace std;

class PokerCard {
 public:
  PokerCard(std::string s, int f) {
    suit = s;
    face = f;
  }

  friend std::ostream &operator<<(std::ostream &out, const PokerCard &p) {
    out << "[" << p.face << " of " << p.suit << "]";
    return out;
  }

  bool operator>(PokerCard &b) {
    return faceValue(face) > faceValue(b.face) ||
           (face == b.face) && suit[0] > b.suit[0];
  }

  bool operator<(PokerCard &b) {
    return faceValue(face) < faceValue(b.face) ||
           ((face == b.face) && suit[0] < b.suit[0]);
  }

  bool operator==(PokerCard &b) { return (face == b.face) && (suit == b.suit); }

  static int faceValue(const int &face) { return (face - 1) ? (face - 1) : 13; }

 private:
  std::string suit;
  int face;
};
