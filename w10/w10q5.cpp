#include <iostream>

using namespace std;

int main() {
  int r, c, number = 1;
  do {
    cin >> r >> c;
    if (!(r && c)) break;
    char field[r][c];
    for (int i = 0; i < r; i++) {
      string row;
      cin >> row;
      for (int j = 0; j < c; j++) field[i][j] = row[j];
    }
    for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++)
        if (field[i][j] != '*') {
          int count = 0;
          for (int ii = i - 1; ii <= i + 1; ii++)
            for (int ij = j - 1; ij <= j + 1; ij++)
              if (ii >= 0 && ii < r && ij >= 0 && ij < c &&
                  field[ii][ij] == '*')
                count++;

          field[i][j] = '0' + count;
        }
    cout << "Field #" << number << ":" << endl;
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) cout << field[i][j];
      cout << endl;
    }
    cout << endl;
    number++;
  } while (true);
}