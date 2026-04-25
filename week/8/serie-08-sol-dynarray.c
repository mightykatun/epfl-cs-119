#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct dynarray {
  size_t size;
  int *items;
} dynarray_t;

dynarray_t create_dynarray() {
  int *items = (int *) malloc(0);
  dynarray_t array = { 0, items };
  return array;
}

void free_dynarray(dynarray_t *array) {
  free(array->items);
}

/* Remplace les items du tableau par new_items de taille new_size.
 * Libère les anciens items.
 *
 * Cette fonction rassemble du travail en commun entre dynarray_add et
 * dynarray_shrink.
 */
void dynarray_swap_items(dynarray_t *array, size_t new_size, int *new_items) {
  free(array->items);
  array->size = new_size;
  array->items = new_items;
}

void dynarray_add(dynarray_t *array, int value) {
  int *new_items = (int *) malloc((array->size + 1) * sizeof(int));

  // Recopier les éléments existants
  for (size_t i = 0; i < array->size; i++) {
    new_items[i] = array->items[i];
  }

  // Stocker le nouvel élément
  new_items[array->size] = value;

  // Remplacer les items
  dynarray_swap_items(array, array->size + 1, new_items);
}

size_t dynarray_size(const dynarray_t *array) {
  return array->size;
}

int dynarray_get(const dynarray_t *array, size_t index) {
  assert(index < array->size);
  return array->items[index];
}

void dynarray_set(dynarray_t *array, size_t index, int new_value) {
  assert(index < array->size);
  array->items[index] = new_value;
}

void dynarray_shrink(dynarray_t *array, size_t new_size) {
  assert(new_size <= array->size);

  int *new_items = (int *) malloc(new_size * sizeof(int));

  // Recopier les éléments qui restent
  for (size_t i = 0; i < new_size; i++) {
    new_items[i] = array->items[i];
  }

  // Remplacer les items
  dynarray_swap_items(array, new_size, new_items);
}

/* Lit des entiers au clavier tant qu'ils sont positifs ou nuls.
 * Renvoie un tableau dynamique des entiers lus.
 */
dynarray_t read_values() {
  dynarray_t values = create_dynarray();

  int value;
  do {
    scanf("%d", &value);
    if (value >= 0)
      dynarray_add(&values, value);
  } while (value >= 0);

  return values;
}

/* Échange les éléments aux indices i et j du tableau dynamique donné.
 * Correspond à l'algorithme "permuter" de ICC-T.
 */
void swap(dynarray_t *array, size_t i, size_t j) {
  int temp = dynarray_get(array, i);
  dynarray_set(array, i, dynarray_get(array, j));
  dynarray_set(array, j, temp);
}

/* Insère l'élément à l'indice i à sa bonne place parmi les éléments [0, i[.
 * Correspond à l'algorithme "insérer" de ICC-T.
 */
void insert(dynarray_t *array, size_t i) {
  for (size_t j = i; j > 0 && dynarray_get(array, j) < dynarray_get(array, j - 1); j--) {
    swap(array, j, j - 1);
  }
}

/* Trie les éléments du tableau avec l'algorithme de tri par insertion.
 * Correspond à l'algorithme "tri par insertion" de ICC-T.
 */
void insertion_sort(dynarray_t *array) {
  size_t n = dynarray_size(array);
  for (size_t i = 1; i < n; i++) {
    if (dynarray_get(array, i) < dynarray_get(array, i - 1)) {
      insert(array, i);
    }
  }
}

/* Affiche les éléments du tableau, un par ligne.
 */
void print_array(const dynarray_t *array) {
  size_t n = dynarray_size(array);
  for (size_t i = 0; i < n; i++) {
    printf("%d\n", dynarray_get(array, i));
  }
}

int main() {
  dynarray_t values = read_values();
  insertion_sort(&values);
  print_array(&values);
  free_dynarray(&values);

  return 0;
}
