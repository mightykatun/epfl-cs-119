#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// toujours via malloc
typedef struct cell {
  int value;
  struct cell *next; // comme si cell_t *next
} cell_t;

// toujours en local
typedef struct intlist {
  cell_t *head;
  cell_t *last;
} intlist_t;

void test_all() {
}

void show_list(const intlist_t *list) {
  /*cell_t *current = list->head;
  while (current != NULL) {
    printf("%d\n", current->value);
    current = current->next;
  }*/
  for (cell_t *current = list->head; current != NULL; current = current->next) {
    printf("%d\n", current->value);
  }
}

void add_first(intlist_t *list, int new_value) {
  cell_t *new_cell = (cell_t *) malloc(sizeof(cell_t));
  new_cell->value = new_value;
  new_cell->next = list->head;
  list->head = new_cell;

  if (list->last == NULL) {
    list->last = new_cell;
  }
}

void add_last(intlist_t *list, int new_value) {
  cell_t *new_cell = (cell_t *) malloc(sizeof(cell_t));
  new_cell->value = new_value;
  new_cell->next = NULL;
  list->last->next = new_cell;
  list->last = new_cell;
}

void free_list(intlist_t *list) {
  cell_t *prev = NULL;
  for (cell_t *current = list->head; current != NULL; current = current->next) {
    if (prev != NULL)
      free(prev);
    prev = current;
  }
  if (prev != NULL)
    free(prev);
}

int main() {
  test_all();

  //cell_t second = { 5, NULL };
  //cell_t first = { 42, &second };

  intlist_t list = { NULL, NULL };
  add_first(&list, 5);
  add_first(&list, 42);

  show_list(&list);

  add_first(&list, 36);
  show_list(&list);

  add_last(&list, 123);
  show_list(&list);

  free_list(&list);

  printf("Lecture 10\n");

  return 0;
}

