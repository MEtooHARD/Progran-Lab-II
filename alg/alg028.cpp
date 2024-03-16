#include <iostream>

using namespace std;

void quicksort(int *data, int left, int right);

int main() {
  int n = 1;
  while (n) {
    cin >> n;
    if (!n) break;

    int ages[n];
    for (int i = 0; i < n; i++) cin >> ages[i];
    /*  for (int i = 0; i < n - 1; i++)
       for (int j = i + 1; j < n; j++)
         if (ages[i] > ages[j]) swap(ages[i], ages[j]);
  */

    quicksort(ages, 0, n - 1);
    cout << ages[0];
    for (int i = 1; i < n; i++) cout << " " << ages[i];
    cout << "\n";
  }
}

void quicksort(int *data, int left, int right) {
  if (left >= right) return;

  int i = left;
  int j = right;
  int key = data[left];

  while (i != j) {
    while (data[j] > key and i < j) j -= 1;
    while (data[i] <= key and i < j) i += 1;
    if (i < j) swap(data[i], data[j]);
  }
  data[left] = data[i];
  data[i] = key;

  quicksort(data, left, i - 1);
  quicksort(data, i + 1, right);
}