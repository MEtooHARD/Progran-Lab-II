#include <iostream>

using namespace std;

class Rang {
 private:
  char **a;

 public:
  Rang(char **a) : a(a) {}
  int Xrange(int i, int j, int M, int N) {
    int add = 1;
    if (i == 0 || j == 0 || i == M - 1 || j == N - 1) {
      return 1;  // 如果在邊邊則範圍為1
    }

    char center = a[i][j];
    int u = 1;

    while (true) {
      // 檢查邊界
      if (i - u < 0 || j - u < 0 || i + u >= M || j + u >= N) {
        break;
      }

      // 檢查正方形邊界是否所有元素都相同
      bool allEqual = true;
      for (int x = i - u; x <= i + u; ++x) {
        if (a[x][j - u] != center || a[x][j + u] != center) {
          allEqual = false;
          break;
        }
      }
      for (int y = j - u; y <= j + u; ++y) {
        if (a[i - u][y] != center || a[i + u][y] != center) {
          allEqual = false;
          break;
        }
      }

      if (!allEqual) {
        break;
      }

      add += 2;
      u++;
    }

    return add;
  }
};

int main() {
  int testnum, M, N, Q, X, Y;
  cin >> testnum;
  while (testnum != 0) {
    cin >> M >> N >> Q;

    char **map = new char *[M];
    for (int i = 0; i < M; i++) {
      map[i] = new char[N];
    }

    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        cin >> map[i][j];
      }
    }

    Rang r(map);

    cout << M << " " << N << " " << Q << endl;
    for (int i = 0; i < Q; i++) {
      cin >> X >> Y;
      cout << r.Xrange(X, Y, M, N) << endl;
    }

    testnum--;
  }
}