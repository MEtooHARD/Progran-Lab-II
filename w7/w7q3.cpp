#include <iostream>

using namespace std;

template <class T>
class Set {
 public:
  Set() : count(0) {}
  Set(const Set<T> &set) {
    count = set.count;
    for (int i = 0; i < count; i++) element[i] = set.element[i];
  }

  int add(const T &toAdd) {
    if (includes(toAdd)) return 0;

    element[count++] = toAdd;
    return 1;
  }

  int add(const Set<T> &set) {
    int duplicates = 0;
    for (int i = 0; i < set.count; i++) {
      if (includes(set.element[i]))
        duplicates++;
      else
        element[i + count - duplicates] = set.element[i];
    }
    count += set.count - duplicates;
    return set.count - duplicates;
  }

  void display() const {
    int j;
    for (j = 0; j < count; j++) std::cout << element[j] << " ";
  }

  bool includes(T el) const {
    int i;
    for (i = 0; i < count; i++)
      if (element[i] == el) return true;
    return false;
  }

  Set operator+(Set<T> set) {
    Set<T> newSet(*this);
    newSet.add(set);
    return newSet;
  }

  Set operator-(const Set<T> &set) {
    Set<T> newSet;
    for (int i = 0; i < count; i++)
      if ((includes(element[i]) && set.includes(element[i])))
        newSet.add(element[i]);
    for (int i = 0; i < set.count; i++)
      if ((includes(set.element[i]) && set.includes(set.element[i])))
        newSet.add(set.element[i]);
    return newSet;
  }

 private:
  T element[100];
  int count = 0;
};

int main() {
  Set<int> set;
  for (int i = 0; i < 5; i++) set.add(i);
  Set<int> det;
  for (int i = 3; i < 8; i++) det.add(i);

  (set + det).display();
  cout << endl;
  (set - det).display();
  cout << endl;
  //   set.display();
  //   cout << endl;
  //   det.display();
  //   cout << endl;
  //   cout << endl;
  //   set.add(*det);
  //   set.display();
  //   cout << endl;
}