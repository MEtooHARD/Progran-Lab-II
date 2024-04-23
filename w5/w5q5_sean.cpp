#include <bits/stdc++.h>

using namespace std;

class Street {
  vector<int> s;

 public:
  Street() {}
  void set(int i) {
    int in;
    cin >> in;
    s.push_back(in);
  }
  int mid() {
    sort(s.begin(), s.end());
    return s[(s.size() - 1) / 2];
  }
};
class Avenue {
  vector<int> a;

 public:
  Avenue() {}
  void set(int i) {
    int in;
    cin >> in;
    a.push_back(in);
  }
  int mid() {
    sort(a.begin(), a.end());
    return a[(a.size() - 1) / 2];
  }
};
int main() {
  int t;
  cin >> t;
  while (t--) {
    Street s;
    Avenue a;
    int f;
    cin >> f >> f >> f;
    for (int i = 0; i < f; i++) {
      s.set(i);
      a.set(i);
    }
    cout << "(Street: " << s.mid() << ", Avenue: " << a.mid() << ")" << endl;
  }
}