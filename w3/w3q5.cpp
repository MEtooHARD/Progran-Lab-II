#include <iostream>
#include <string>
using namespace std;

class Register {
  string r = "01000";

 public:
  void format(int num) {
    int x = 4;
    while (num > 0) {
      r[x--] = num % 2 + '0';
      num /= 2;
    }
  }
  string get_r() { return r; }
};

class code {
  Register t[8];
  string i1, i2, i3;
  int imm = 0;
  string toBase2(int n) {
    string r = "0000000000000000";
    int i = 15;
    while (n > 0) {
      r[i--] = n % 2 + '0';
      n /= 2;
    }
    return r;
  }
  int toBase10(string n) {
    int r = 0, pow = 1, i = 4;
    while (i >= 0) {
      r += (n[i--] - '0') * pow;
      pow *= 2;
    }
    return r;
  }
  int get_num(string s) { return s[2] - '0'; }

  string instruction(string n) {
    if (n == "add")
      return "100000";
    else if (n == "sub")
      return "100010";
    else if (n == "or")
      return "100101";
    else if (n == "and")
      return "100100";
  }

 public:
  code() {
    for (int i = 0; i < 8; i++) t[i].format(i);
  }
  void command(string n) {
    if (n == "add" || n == "sub" || n == "or" || n == "and") {
      cin >> i1 >> i2 >> i3;
      cout << "000000";
      cout << t[get_num(i2)].get_r() << t[get_num(i3)].get_r()
           << t[get_num(i1)].get_r();
      cout << "00000" << instruction(n);
    } else {
      cin >> i1 >> i2 >> imm;
      cout << "001000";
      cout << t[get_num(i1)].get_r() << t[get_num(i2)].get_r();
      cout << toBase2(imm);
    }
    cout << endl;
  }
};

int main() {
  string in;
  code c;
  while (cin >> in) {
    c.command(in);
  }
}