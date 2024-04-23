#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
  friend class Group;
  int street, avenue;

 public:
  static bool compareStreet(Person &p1, Person &p2) {
    return p1.street < p2.street;
  }
  static bool compareAvenue(Person &p1, Person &p2) {
    return p1.avenue < p2.avenue;
  }

  Person(int _street, int _avenue) : street(_street), avenue(_avenue) {}
  string toString() {
    return (*(new string("(Street: ")))
        .append(to_string(street))
        .append(", Avenue: ")
        .append(to_string(avenue))
        .append(")");
  }
};

class Group {
  vector<Person> person;

 public:
  void addPerson(int street, int avenue) {
    person.push_back(*(new Person(street, avenue)));
  }

  Person *meetingPoint() {
    int street, avenue;
    sort(person.begin(), person.end(), Person::compareStreet);
    street = person[(person.size() - 1) / 2].street;
    sort(person.begin(), person.end(), Person::compareAvenue);
    avenue = person[(person.size() - 1) / 2].avenue;
    return new Person(street, avenue);
  }
};

int main() {
  int t;
  cin >> t;
  while (t--) {
    int s, a, f;
    cin >> f >> f >> f;
    Group g;
    for (int i = 0; i < f; i++) {
      cin >> s >> a;
      g.addPerson(s, a);
    }
    cout << g.meetingPoint()->toString() << endl;
  }
}