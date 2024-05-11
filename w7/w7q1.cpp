#include <iostream>

using namespace std;

template <typename T>

void sort(T *array, int n) {
  qsort(array, n, sizeof(T),
        [](const void *a, const void *b) { return (int)(*(T *)a > *(T *)b); });
}