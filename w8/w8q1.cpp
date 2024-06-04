#include <iostream>
#include <ostream>

using namespace std;

class LinkedList {
 public:
  class Node {
   public:
    Node() : next(nullptr), data(0) {}
    Node(int d) : next(nullptr), data(d) {}
    Node(Node* n) : next(n), data(0) {}
    Node(Node* n, int d) : next(n), data(d) {}
    int data;
    Node* next = NULL;
  };

  LinkedList() {}

  ~LinkedList() {
    Node *node = head, *temp = NULL;
    while (node != NULL) {
      temp = node->next;
      delete node;
      node = temp;
    }
  }

  bool addFromHead(int d) {
    Node* temp = new Node(d);
    // if (temp == NULL) return false;
    temp->next = head;
    head = temp;
    size++;
    return true;
  }

  bool addFromTail(int d) {
    Node *temp = head, *newNode = new Node(d);
    // if (newNode == NULL) return false;
    if (head == NULL)
      head = newNode;
    else {
      while (temp->next != NULL) temp = temp->next;
      temp->next = newNode;
    }
    size++;
    return true;
  }

  bool removeFromHead() {
    if (head == NULL) return false;
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
    return true;
  }

  bool removeFromTail() {
    if (head == NULL) return false;
    Node* temp = head;
    if (head->next == NULL) {
      delete head;
      head = NULL;
    } else {
      while (temp->next->next != NULL) temp = temp->next;
      delete temp->next;
      temp->next = NULL;
    }
    size--;
    return true;
  }

  friend ostream& operator<<(ostream& o, LinkedList* l) {
    o << '{';
    if (l != NULL && l->head != NULL) {
      o << l->head->data;
      Node* temp = l->head->next;
      while (temp != NULL) {
        o << ", " << temp->data;
        temp = temp->next;
      }
    }
    o << '}' << '\n';
    return o;
  }

  size_t getSize() const { return size; }

 protected:
  size_t size = 0;
  Node* head = NULL;
};

template <class T>
class Set : public LinkedList {
 public:
  Set() {}

  bool addElement(T el) {
    if (head == nullptr) return false;
    if (head->data >= el) {
      Node* newNode = new Node(el);
      newNode->next = head;
      head = newNode;
      return true;
    }
    if (head->next == nullptr) {
      Node* newNode = new Node(el);
      head->next = newNode;
      return true;
    }
    bool include = false;
    Node* temp = head;
    while (temp->next != nullptr) {
      if (temp->next->data >= el) {
        Node* newNode = new Node(el);
        newNode->next = temp->next;
        temp->next = newNode;
        return true;
      }
      temp = temp->next;
    }
    temp->next = new Node(el);
    return true;
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

 private:
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