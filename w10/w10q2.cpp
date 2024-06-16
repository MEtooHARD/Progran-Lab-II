#include <iostream>

using namespace std;

char trans(char a) {
  if (a == 'd' || a == 'D')
    a = 'a';
  else if (a == 'm' || a == 'M')
    a = 'b';
  else if (a == 'b' || a == 'B')
    a = 'c';
  else if (a == 'g' || a == 'G')
    a = 'd';
  else if (a == 't' || a == 'T')
    a = 'e';
  else if (a == 'h' || a == 'H')
    a = 'f';
  else if (a == 'j' || a == 'J')
    a = 'g';
  else if (a == 'k' || a == 'K')
    a = 'h';
  else if (a == 'p' || a == 'P')
    a = 'i';
  else if (a == 'l' || a == 'L')
    a = 'j';
  else if (a == ';' || a == ':')
    a = 'k';
  else if (a == '\'' || a == '\"')
    a = 'l';
  else if (a == '.' || a == '>')
    a = 'm';
  else if (a == ',' || a == '<')
    a = 'n';
  else if (a == '[' || a == '{')
    a = 'o';
  else if (a == ']' || a == '}')
    a = 'p';
  else if (a == 'e' || a == 'E')
    a = 'q';
  else if (a == 'y' || a == 'Y')
    a = 'r';
  else if (a == 'f' || a == 'F')
    a = 's';
  else if (a == 'u' || a == 'U')
    a = 't';
  else if (a == 'o' || a == 'O')
    a = 'u';
  else if (a == 'n' || a == 'N')
    a = 'v';
  else if (a == 'r' || a == 'R')
    a = 'w';
  else if (a == 'v' || a == 'V')
    a = 'x';
  else if (a == 'i' || a == 'I')
    a = 'y';
  else if (a == 'c' || a == 'C')
    a = 'z';
  else if (a == 'a' || a == 'A')
    a = 'z';
  return a;
}

int main() {
  string input;
  // getline(cin, input);
  while (getline(cin, input)) {
    for (int i = 0; i < input.length(); i++) cout << trans(input[i]);
    cout << endl;
  }
  // cout << endl;
}