#include <iostream>

using namespace std;

int main() {
  int i, j;
  while (cin >> i >> j) {
    int maxLen = 0, a = i, b = j;
    if (i > j) {
      b = i;
      a = j;
    }
    for (int l = a, current, n; l <= b; l++) {
      n = l;
      current = 1;
      while (n > 1) {
        if (n % 2)
          n = n * 3 + 1;
        else
          n /= 2;
        current++;
      }
      if (maxLen < current) maxLen = current;
    }
    cout << i << " " << j << " " << maxLen << endl;
  }
}