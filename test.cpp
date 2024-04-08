#include <iostream>

using namespace std;

class Dick {
  void cum() {}

  ~Dick() {
    for (int i = 0; i < 999999999; i++) cum();
  }
};

int main() {
  int** matrix = (int**)malloc(sizeof(int*) * 10);

  for (int i = 0; i < 10; i++) {
    int* list[10] = {};
    int* gg;
    // matrix[i] = list;
    matrix[i] = gg;
  }

  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++) cout << matrix[i][j];
}
