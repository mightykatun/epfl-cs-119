#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

int affiche(const int mat[], size_t m, size_t n) {
  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      printf("%d ", mat[i*n + j]);
    }
    printf("\n");
  }

  return 0;
}

void swap(int *pa, int *pb) {
  int temp = *pa; // déréférencement
  *pa = *pb;
  *pb = temp;
}

int main() {
  printf("Lecture 6\n");

  size_t m, n;
  scanf("%lu %lu", &m, &n);
  int mat[m * n];
  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      int elem;
      scanf("%d", &elem);
      mat[i*n + j] = elem;
    }
  }

  affiche(mat, m, n);

  int x, y;
  scanf("%d %d", &x, &y);
  printf("%d %d\n", x, y);
  // échanger x et y
  swap(&x, &y);
  printf("%d %d\n", x, y);

  return 0;
}

