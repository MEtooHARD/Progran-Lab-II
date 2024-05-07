#include <iostream>
#include <ostream>

using namespace std;

class LinkedList {
 public:
  class Node {
   public:
    Node() : next(nullptr), data(0) {}
    Node(int d) : next(nullptr), data(d) {}
    Node(Node *n) : next(n), data(0) {}
    Node(Node *n, int d) : next(n), data(d) {}
    int data;
    Node *next = NULL;
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
    Node *temp = new Node(d);
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
    Node *temp = head;
    head = head->next;
    delete temp;
    size--;
    return true;
  }

  bool removeFromTail() {
    if (head == NULL) return false;
    Node *temp = head;
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

  friend ostream &operator<<(ostream &o, LinkedList *l) {
    o << '{';
    if (l != NULL && l->head != NULL) {
      o << l->head->data;
      Node *temp = l->head->next;
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
  Node *head = NULL;
};

/* int main() {
  LinkedList *list = new LinkedList();
  cout << list;
  list->addFromHead(5);
  cout << list;
  list->addFromTail(4);
  cout << list;
  list->addFromHead(6);
  cout << list;
  cout << list->getSize() << '\n';
  list->removeFromHead();
  cout << list;
  list->removeFromTail();
  cout << list;
  cout << list->getSize();
}
 */