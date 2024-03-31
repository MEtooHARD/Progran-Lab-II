#include <iostream>
#include <vector>

using namespace std;

int abs(int num) { return (num < 0) ? -num : num; }

enum class Direction { UP, RIGHT, DOWN, LEFT, NOTASIDE };

class Point {
 protected:
  int x = 0, y = 0;

 public:
  Point() {}
  Point(int _x, int _y) : x(_x), y(_y) {}

  int getX() { return x; }
  int getY() { return y; }
  void setX(int _x) { x = _x; }
  void setY(int _y) { y = _y; }
};

class Cell : public Point {
 protected:
  bool around[4] = {}, visited = false;
  /*   U          0       _
   * L C R  ->  3 C 1    |_|
   *   D          2
   */
 public:
  static const int a = 0;

  Cell() : Point(1, 1) {}
  Cell(int _x, int _y) : Point(_x, _y) {}

  Point* toPatternCoordinate() { return new Point((x - 1) * 2 + 1, x - 1); }

  Direction relativeDirect(Cell* T) {
    if (x - T->x == 1 && y == T->y)
      return Direction::DOWN;
    else if (T->x - x == 1 && y == T->y)
      return Direction::UP;
    else if (y - T->y == 1 && x == T->x)
      return Direction::LEFT;
    else if (T->y - y == 1 && x == T->x)
      return Direction::RIGHT;

    return Direction::NOTASIDE;
  }

  void setAccess(Direction direct, bool accessibility) {
    if (direct != Direction::NOTASIDE)
      around[(int)direct] = accessibility;
    else
      cout << "Seems something went wrong when assigning next direction.";
  }
};

class Maze {
 private:
  int rows, cols;
  Cell** cells;
  Cell start;
  vector<Cell> list;

 public:
  Maze() {
    cin >> rows >> cols;
    cells = (Cell**)malloc(sizeof(Cell*) * rows);
    for (int i = 0; i < cols; i++)
      cells[i] = (Cell*)malloc(sizeof(Cell) * cols);

    for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols; j++) cells[i][j] = *(new Cell(i + 1, j + 1));

    int x, y;
    cin >> x >> y;
    start.setX(x);
    start.setY(y);
  }

  char** initialPattern() {
    char** pattern = (char**)malloc(sizeof(char*) * (rows + 1));
    for (int i = 0; i <= rows; i++)
      pattern[i] = (char*)malloc(sizeof(char) * (cols * 2 + 1));

    // top
    for (int j = 0; j < cols * 2; j++) pattern[rows][j] = (j % 2) ? '_' : ' ';

    // others
    for (int i = 0; i < rows; i++)
      for (int j = 0; j <= cols * 2; j++) pattern[i][j] = (j % 2) ? '_' : '|';

    return pattern;
  }

  void modifyPattern() {}

  char** calcPattern() { return initialPattern(); }

  // void

  void print() {
    char** pattern = calcPattern();
    for (int i = rows; i >= 0; i--) {
      for (int j = 0; j <= cols * 2; j++) cout << pattern[i][j];
      cout << endl;
    }
  }
};

int main() {
  // int cases;
  // cin >> cases;

  // for (int i = 0; i < cases; i++) {
  //   Maze maze;
  //   maze.print();
  // }

  Cell C(5, 4);
  Point* cor = C.toPatternCoordinate();
  cout << '(' << cor;
}
