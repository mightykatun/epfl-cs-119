#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int *make_squares(size_t n) {
  //int squares[n];
  int *squares = (int *) malloc(n * sizeof(int));
  for (size_t i = 0; i < n; i++) {
    squares[i] = i * i;
  }
  return squares;
}

typedef struct train {
  size_t carriage_count;
  int *persons_by_car;
} train_t;

train_t create_train(size_t carriage_count) {
  train_t train;
  train.carriage_count = carriage_count;
  train.persons_by_car = (int *) malloc(carriage_count * sizeof(int));
  return train;
}

void free_train(train_t *train) {
  //free((*train).persons_by_car);
  free(train->persons_by_car);
}

int main() {
  printf("Lecture 8\n");

  int *squares = make_squares(5);
  printf("%d\n", squares[3]);

  free(squares); // libérer la mémoire

  train_t train = create_train(5);
  train_t train2 = create_train(10);

  // utiliser train et train2

  //free(train.persons_by_car); // pas terrible
  free_train(&train);
  free_train(&train2);

  // ici on ne peut surtout plus utiliser train et train2

  //int x;
  // free(&x); // KO!

  return 0;
}

