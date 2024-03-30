#include <iostream>

using namespace std;

class Anagram : public string {
  int composition[26] = {};

 public:
  Anagram(string the_world) {  // （確信
    for (string::iterator it = the_world.begin(); it != the_world.end(); it++)
      if ('a' <= *it && *it <= 'z')
        composition[*it - 'a']++;
      else if ('A' <= *it && *it <= 'Z')
        composition[*it - 'A']++;
      else
        continue;
  }

  void printInfo() const {
    for (int i = 0; i < 26; i++)
      if (composition[i])
        cout << (char)('A' + i) << ": " << composition[i] << endl;
  }

  int getCharCount(int i) { return composition[i]; }

  bool operator==(Anagram &str) const {
    int i;
    for (i = 0; i < 26; i++)
      if (composition[i] != str.getCharCount(i)) break;
    return i == 26;
  };
};

int main() {
  Anagram ana("monkeys write"), ana2("New York Times");

  cout << (ana == ana2) << endl;
}
