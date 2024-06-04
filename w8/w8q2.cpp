#include <iostream>
using namespace std;

template <class T>
class LinkedList {
 public:
  class Node {
   public:
    Node() : next(nullptr), data(0) {}
    Node(T d) : next(nullptr), data(d) {}
    Node(Node* n) : next(n), data(0) {}
    Node(Node* n, T d) : next(n), data(d) {}
    T data;
    Node* next;
  };
  LinkedList() : head(nullptr) {}
  ~LinkedList() {
    while (head) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }
  bool addFromHead(T d) {
    if (head) {
      head = new Node(head, d);
    } else {
      head = new Node(d);
    }
    return true;
  }
  bool addFromTail(T d) {
    if (!head) {
      head = new Node(d);
    } else {
      Node* tail = head;
      while (tail->next) tail = tail->next;
      tail->next = new Node(d);
    }
    return true;
  }
  bool removeFromHead() {
    if (head) {
      Node* temp = head;
      head = head->next;
      delete temp;
      return true;
    }
    return false;
  }
  bool removeFromTail() {
    if (head) {
      if (!head->next) {
        delete head;
        head = nullptr;
        return true;
      }
      Node* temp = head;
      while (temp->next->next) temp = temp->next;
      delete temp->next;
      temp->next = nullptr;
      return true;
    }
    return false;
  }
  friend ostream& operator<<(ostream& o, LinkedList* l) {
    Node* current = l->head;
    o << "[";
    while (current) {
      o << current->data;
      if (current->next) {
        o << ", ";
      }
      current = current->next;
    }
    o << "]";
    return o;
  }
  size_t getSize() const {
    size_t size = 0;
    Node* current = head;
    while (current) {
      size++;
      current = current->next;
    }
    return size;
  }
  int searchData(int d) {
    Node* current = head;
    int index = 0;
    while (current) {
      if (current->data == d) {
        return index;
      }
      current = current->next;
      index++;
    }
    return -1;
  }
  T operator[](int i) {
    Node* current = head;
    int index = 0;
    while (current) {
      if (index == i) {
        return current->data;
      }
      current = current->next;
      index++;
    }
    throw out_of_range("Index out of range");
  }

 protected:
  Node* head;
};

template <class T>
class Set : private LinkedList<T> {
 public:
  Set() : LinkedList<T>() {}
  ~Set() {}
  bool addElement(T d) {
    if (!contains(d)) {
      this->addFromTail(d);
      amount++;
      return true;
    }
    return false;
  }

  friend ostream& operator<<(ostream& o, Set<T>* s) {
    if (!s->head) {
      o << "{}\n";
      return o;
    }
    o << "{";
    typename LinkedList<T>::Node* current = s->head;
    bool first = true;
    while (current) {
      if (!first) {
        o << ", ";
      }
      o << current->data;
      first = false;
      current = current->next;
    }
    o << "}\n";
    return o;
  }

  Set<T>* operator+(Set<T>* s) {
    Set<T>* result = new Set<T>();
    typename LinkedList<T>::Node* current = this->head;
    while (current) {
      result->addElement(current->data);
      current = current->next;
    }
    current = s->head;
    while (current) {
      result->addElement(current->data);
      current = current->next;
    }
    return result;
  }

  Set<T>* operator-(Set<T>* s) {
    Set<T>* result = new Set<T>();
    typename LinkedList<T>::Node* current = this->head;
    while (current) {
      if (!s->contains(current->data)) {
        result->addElement(current->data);
      }
      current = current->next;
    }
    return result;
  }

  Set<T>* operator*(Set<T>* s) {
    Set<T>* result = new Set<T>();
    typename LinkedList<T>::Node* current = this->head;
    while (current) {
      if (s->contains(current->data)) {
        result->addElement(current->data);
      }
      current = current->next;
    }
    return result;
  }

  bool operator==(Set<T>* s) {
    if (amount == s->amount) {
      typename LinkedList<T>::Node* current = this->head;
      while (current) {
        if (!s->contains(current->data)) return false;
        current = current->next;
      }
      return true;
    }
    return false;
  }

  bool operator>(Set<T>* s) {
    if (amount <= s->amount) return false;
    typename LinkedList<T>::Node* current = s->head;
    while (current) {
      if (!contains(current->data)) return false;
      current = current->next;
    }
    return true;
  }

  bool operator<(Set<T>* s) {
    if (amount >= s->amount) return false;
    typename LinkedList<T>::Node* current = this->head;
    while (current) {
      if (!s->contains(current->data)) return false;
      current = current->next;
    }
    return true;
  }

  bool operator>=(Set<T>* s) {
    if (amount < s->amount) return false;
    typename LinkedList<T>::Node* current = s->head;
    while (current) {
      if (!contains(current->data)) return false;
      current = current->next;
    }
    return true;
  }

  bool operator<=(Set<T>* s) {
    if (amount > s->amount) return false;
    typename LinkedList<T>::Node* current = this->head;
    while (current) {
      if (!s->contains(current->data)) return false;
      current = current->next;
    }
    return true;
  }

 private:
  int amount = 0;
  bool contains(T d) {
    typename LinkedList<T>::Node* current = this->head;
    while (current) {
      if (current->data == d) {
        return true;
      }
      current = current->next;
    }
    return false;
  }
};