#include <iostream>
#include <string>

using namespace std;

string stop("stop"), left("left"), right("right"),
    cannotRotate("No element in matrix can be rotated."),
    cannotBePrinted("No element in matrix can be printed."), unknown("unknown"),
    print("print"), scan("scan"), rotate("rotate");

void readInt(int* i) {
  int input;
  cin >> input;
  *i = input;
}

void printInt(int* i) { cout << *i; }

class SquareMatrix {
 private:
  int size = 0;
  int** matrix = (int**)malloc(sizeof(int*));
  /* direction. between(include) 0 & 3. each 1s means clockwise-rotated 90 deg*/
  int direction = 0;

 public:
  /* assigns memories to the matrix */
  void initMatrixSpace() {
    free(matrix);
    matrix = (int**)malloc(sizeof(int*) * size);
    for (int i = 0; i < size; i++) matrix[i] = (int*)malloc(sizeof(int) * size);
  }

  /* sets the size of the matrix and initialize and reset direction (as 0)*/
  void setSize(int _size) {
    size = _size;
    direction = 0;
    initMatrixSpace();
  }

  /* reads elements */
  void readElements() { forEach(readInt); }

  /* prints matrix depending on the direction */
  void print() {
    switch (direction) {
      case 0:
        for (int i = 0; i < size; i++) {
          for (int j = 0; j < size; j++) cout << matrix[i][j] << ' ';
          cout << endl;
        }
        break;
      case 1:
        for (int j = 0; j < size; j++) {
          for (int i = size - 1; i >= 0; i--) cout << matrix[i][j] << ' ';
          cout << endl;
        }
        break;
      case 2:
        for (int i = size - 1; i >= 0; i--) {
          for (int j = size - 1; j >= 0; j--) cout << matrix[i][j] << ' ';
          cout << endl;
        }
        break;
      case 3:
        for (int j = size - 1; j >= 0; j--) {
          for (int i = 0; i < size; i++) cout << matrix[i][j] << ' ';
          cout << endl;
        }
        break;
    }
    cout << endl;
  }

  /* changes the direction of printing */
  int rotate(int dir) {
    int temp = direction + dir;
    if (temp < 0) temp += 4;
    direction = temp % 4;
    return direction;
  }

  /* goes through all elements in direction 0. use the elements' addresses
   * as params of the given function */
  typedef void func(int* e);
  void forEach(func F) {
    for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++) F(&matrix[i][j]);
  }

  /* returns direction */
  int getDirection() { return direction; }
};

int main() {
  bool read = false;
  int size;
  string commando;
  SquareMatrix matrix;
  while (commando != stop) {  // stop
    cin >> commando;
    if (commando == rotate) {  // rotate
      cin >> commando;
      if (read) {
        if (commando == "right")
          matrix.rotate(1);
        else if (commando == "left")
          matrix.rotate(-1);
      } else
        cout << cannotRotate << endl;
    } else if (commando == print) {  // print
      if (read)
        matrix.print();
      else
        cout << cannotBePrinted << endl;
    } else if (commando == scan) {  // scan
      cin >> size;
      if (size) {
        read = true;
        matrix.setSize(size);
        matrix.readElements();
      } else {
        read = false;
      }
    } else {  // unknown
      if (commando != stop) cout << unknown << endl;
    }
  }
}