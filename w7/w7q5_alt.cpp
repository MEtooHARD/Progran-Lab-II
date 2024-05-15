#include <iostream>
using namespace std;

template <typename Base, typename T>
inline bool instanceof (const T *ptr) {
  return dynamic_cast<const Base *>(ptr) != nullptr;
}

class Container {
 public:
  virtual void push(int) = 0;
  virtual void pop() = 0;
  virtual bool empty() const = 0;
  virtual int top() const = 0;
};

class Stack : public Container {
  int count = 0;
  int elements[100];

 public:
  void push(int n) { elements[count++] = n; }

  void pop() {
    if (empty()) throw out_of_range("1");
    count--;
  }

  bool empty() const { return count == 0; }

  int top() const {
    if (empty()) throw out_of_range("2");
    return elements[count - 1];
  }
};

class PriorityQueue : public Container {
 public:
  int count = 0;
  int elements[100] = {0};

 public:
  void push(int n) {
    if (count == 0)
      elements[count++] = n;
    else {
      for (int i = 0; i < count; i++)
        if (n < elements[i]) {
          for (int j = count++; j > i; j--) elements[j] = elements[j - 1];
          elements[i] = n;
          return;
        }
      elements[count++] = n;
    }
  }

  void pop() {
    if (empty()) throw out_of_range("3");
    count--;
  }

  bool empty() const { return count == 0; }

  int top() const {
    if (empty()) throw out_of_range("4");
    return elements[count - 1];
  }
};

int judge(Container *c) { return instanceof <PriorityQueue>(c) ? 2 : 1; }