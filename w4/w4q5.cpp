#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int abs(int num) { return (num < 0) ? -num : num; }

enum class Direction { UP, RIGHT, DOWN, LEFT, NOTASIDE };

enum class Action { F = 'F', U = 'U', D = 'D', L = 'L', R = 'R' };

Direction ActToDirect(Action A) {
  switch (A) {
    case Action::D:
      return Direction::DOWN;
    case Action::L:
      return Direction::LEFT;
    case Action::R:
      return Direction::RIGHT;
    case Action::U:
      return Direction::UP;
  }
  throw "invalid transfromming of Act to Direct";
}

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

  friend std::ostream& operator<<(std::ostream& out, const Point& P) {
    cout << '(' << P.x << ", " << P.y << ')';
    return out;
  }
};

class Cell : public Point {
  // bool around[4] = {}, visited = false;
  /*   U          0       _
   * L C R  ->  3 C 1    |_|
   *   D          2
   */
  bool visited = false;

 public:
  // static const int a = 0;

  Cell() : Point(1, 1) {}
  Cell(int _x, int _y) : Point(_x, _y) {}

  Point* toPatternCoordinate() const { return new Point(x - 1, y * 2 - 1); }

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

  void setVisited() { visited = true; }
  bool isVisited() { return visited; }
  void print() { cout << '(' << x << ", " << y << ')'; }

  friend std::ostream& operator<<(std::ostream& out, const Cell& C) {
    cout << "C: (" << C.x << ", " << C.y << ")  P: ("
         << C.toPatternCoordinate()->getX() << ", "
         << C.toPatternCoordinate()->getY() << ')';
    return out;
  }

  bool operator==(Cell C) { return x == C.getX() && y == C.getY(); }
  bool operator!=(Cell C) { return !(*this == C); }
};

class Maze {
 private:
  int rows, cols;
  Cell** cells;
  char** pattern;

 public:
  Maze() {
    cin >> rows >> cols;
    cells = (Cell**)malloc(sizeof(Cell*) * rows);
    for (int i = 0; i < cols; i++)
      cells[i] = (Cell*)malloc(sizeof(Cell) * cols);

    for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols; j++) cells[i][j] = *(new Cell(i + 1, j + 1));

    pattern = initialPattern();

    vector<Cell*> list;

    int x, y;
    cin >> x >> y;
    list.push_back(&cells[x - 1][y - 1]);

    char commando;

    while (list.size()) {
      cin >> commando;
      // cout << "commando: " << commando << endl;

      if ((int)commando == (int)Action::F) {
        int nPlace;
        cin >> nPlace;
        reverse(list.begin() + nPlace - 1, list.end());
      } else {
        Cell* toAdd = getRelativeCell(
            list.back(), ActToDirect(static_cast<Action>(commando)));
        if (*toAdd != *list.back()) {
          list.push_back(toAdd);
          list.back()->setVisited();
        }
      }

      int surroundUnvisited = 0;
      for (int i = 0; i < 4; i++)
        if (!getRelativeCell(list.back(), (Direction)i)->isVisited())
          surroundUnvisited++;

      removeWall(list.back(), list[list.size() - 2]);

      cout << "list: " << endl;
      for (vector<Cell*>::iterator i = list.begin(); i < list.end(); i++) {
        cout << **i << endl;
      }

      if (!surroundUnvisited)
        while (!surroundUnvisited) {
          list.pop_back();
          surroundUnvisited = 0;
          for (int i = 0; i < 4; i++)
            if (getRelativeCell(list.back(), (Direction)i)->isVisited())
              surroundUnvisited++;
        }
      print();
      cout << endl;
    }
  }

  char** initialPattern() {
    char** pattern = (char**)malloc(sizeof(char*) * (rows + 1));
    for (int i = 0; i <= rows; i++)
      pattern[i] = (char*)malloc(sizeof(char) * (cols * 2 + 1));

    // top
    for (int j = 0; j <= cols * 2; j++) pattern[rows][j] = (j % 2) ? '_' : ' ';

    // others
    for (int i = 0; i < rows; i++)
      for (int j = 0; j <= cols * 2; j++) pattern[i][j] = (j % 2) ? '_' : '|';

    return pattern;
  }

  Cell* getRelativeCell(Cell* C, Direction D) {
    int x = C->getX() - 1, y = C->getY() - 1;
    switch (D) {
      case Direction::UP:
        x += 1;
        break;
      case Direction::RIGHT:
        y += 1;
        break;
      case Direction::DOWN:
        x -= 1;
        break;
      case Direction::LEFT:
        y -= 1;
    }
    x = (x >= 0 && x < rows) ? x : C->getX() - 1;
    y = (y >= 0 && y < cols) ? y : C->getY() - 1;

    return &cells[x][y];
  }

  void removeWall(Cell* c1, Cell* c2) {
    if (c1 != c2) {
      cout << "remove: " << *c1 << " ~ " << *c2 << endl;
      int x =
          c1->toPatternCoordinate()->getX() + c2->toPatternCoordinate()->getX();
      int y =
          c1->toPatternCoordinate()->getY() + c2->toPatternCoordinate()->getY();

      pattern[x / 2 + (c1->getX() != c2->getX())][y / 2] = ' ';
    }
  }

  void print() {
    for (int i = rows; i >= 0; i--) {
      for (int j = 0; j <= cols * 2; j++) cout << pattern[i][j];
      cout << endl;
    }
  }
};

int main() {
  int cases;
  cin >> cases;

  for (int i = 0; i < cases; i++) {
    Maze maze;
    maze.print();
  }

  /* Cell A(3, 3), B(3, 4);
  cout << A << '\n' << B; */
  // cin >> cases;
  /* Cell C(5, 4);
  Point* cor = C.toPatternCoordinate();
  cout << '(' << cor->getX() << ", " << cor->getY() << ')' << endl; */
}
