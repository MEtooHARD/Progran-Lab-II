#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

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

  friend std::ostream &operator<<(std::ostream &out, const Point &P) {
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
  Cell() : Point(1, 1) {}
  Cell(int _x, int _y) : Point(_x, _y) {}

  Point *toPatternCoordinate() const { return new Point(x - 1, y * 2 - 1); }

  Direction relativeDirect(Cell *T) {
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

  friend std::ostream &operator<<(std::ostream &out, const Cell &C) {
    cout << "C: (" << C.x << ", " << C.y << ")  P: ("
         << C.toPatternCoordinate()->getX() << ", "
         << C.toPatternCoordinate()->getY() << ')';
    return out;
  }

  bool operator==(Cell C) { return x == C.getX() && y == C.getY(); }
  bool operator!=(Cell C) { return !(x == C.getX() && y == C.getY()); }
};

/**
 * cells: Here the Maze is made up in Cells.
 * It's rows height, cols wide, visually.
 *
 * rows
 *  3 • • • •
 *  2 • • • •
 *  1 • • • •
 *    1 2 3 4 cols
 *
 * pattern: The actual thing be printed. In the Maze process it might be
 * modified multiple times.
 *
 * rows-1
 *      _   _   _
 *  2 | _ | _ | _ |
 *  1 | _ | _ | _ |
 *  0 | _ | _ | _ |
 *    0 1 2 3 4 5 6 cols*2 - 1
 *
 * The Maze process is based on Cell coordinates. And when involving the
 * printing pattern it transfers Cell coordinates to pattern coordinates for
 * sake of safely interacting with pattern.
 */
class Maze {
 private:
  int rows, cols;
  Cell **cells;
  char **pattern;

 public:
  Maze() {
    /* initialization */
    // rows & cols
    cin >> rows >> cols;
    cells = (Cell **)malloc(sizeof(Cell *) * rows);
    for (int i = 0; i < rows; i++)
      cells[i] = (Cell *)malloc(sizeof(Cell) * cols);
    // Cells matrix
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols; j++) cells[i][j] = *(new Cell(i + 1, j + 1));
    pattern = initialPattern();
    // declaration: list & Action
    vector<Cell *> list;
    char commando;

    /* start point */
    int x, y;
    cin >> x >> y;
    list.push_back(&cells[x - 1][y - 1]);
    cells[x - 1][y - 1].setVisited();

    /**
     * Action input: U, R, D, L, F (n)
     * Depend on Action: "flip" or "add a cell to list and remove wall".
     * Check surrounding unvisited cells => fit => remove cell from list =>
     * repeat checking.
     * Repeat taking Action input till list is empty.
     * End.
     */
    while (list.size()) {
      cin >> commando;

      if ((int)commando == (int)Action::F) {  // Flip
        int nPlace;
        cin >> nPlace;
        reverse(list.begin() + nPlace - 1, list.end());
      } else {  // Go U/R/D/L
        Cell *toAdd = getRelativeCell(
            list.back(), ActToDirect(static_cast<Action>(commando)));
        if (*toAdd != *list.back()) {
          list.push_back(toAdd);
          list.back()->setVisited();
          removeWall(list.back(), list[list.size() - 2]);
        }
      }
      // test surround unvisited
      int surroundUnvisited = 0;
      for (int i = 0; i < 4; i++)
        if (!getRelativeCell(list.back(), (Direction)i)->isVisited())
          surroundUnvisited++;
      // if no unvisited, remove and repeat.
      while (!surroundUnvisited && list.size()) {
        list.pop_back();
        surroundUnvisited = 0;
        for (int i = 0; i < 4 && list.size(); i++)
          if (!getRelativeCell(list.back(), (Direction)i)->isVisited())
            surroundUnvisited++;
      }
    }
  }

  char **initialPattern() {
    char **pattern = (char **)malloc(sizeof(char *) * (rows + 1));
    for (int i = 0; i <= rows; i++)
      pattern[i] = (char *)malloc(sizeof(char) * (cols * 2 + 1));

    // top
    for (int j = 0; j <= cols * 2; j++) pattern[rows][j] = (j % 2) ? '_' : ' ';

    // others
    for (int i = 0; i < rows; i++)
      for (int j = 0; j <= cols * 2; j++) pattern[i][j] = (j % 2) ? '_' : '|';

    return pattern;
  }

  /* Returns the Cell aside the gicen C Cell and depend on the given Direction
   * and the position of C to actual return the real related Cell or the cell
   * at the same position as C. (for sake of preventing segmentation fault and
   * for algorithm conveniency) */
  Cell *getRelativeCell(Cell *C, Direction D) {
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

  /* Removes the wall between the given Cells c1 and c2. It's simply done by
   * averaging c1 and c2's coordinates. */
  void removeWall(Cell *c1, Cell *c2) {
    if (c1 != c2) {
      int x =
          c1->toPatternCoordinate()->getX() + c2->toPatternCoordinate()->getX();
      int y =
          c1->toPatternCoordinate()->getY() + c2->toPatternCoordinate()->getY();
      pattern[x / 2 + (c1->getX() != c2->getX())][y / 2] = ' ';
    }
  }

  /* Print */
  void print() {
    for (int j = 0; j < cols * 2; j++) cout << pattern[rows][j];

    cout << endl;
    for (int i = rows - 1; i >= 0; i--) {
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
    if (i != cases - 1) cout << endl;
  }
}