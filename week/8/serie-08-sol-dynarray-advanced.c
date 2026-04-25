#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

/* Cette version avancée contient un tableau `items` qui est parfois plus grand
 * que nécessaire. On retient séparément la taille "réelle" du tableau
 * (maximum actuel) de sa taille "logique" (comme avec la pile).
 * Quand on n'a plus de place, on *double* la taille du tableau interne.
 *
 * Cela garantit que si on ajoute n éléments à un tableau vide, on a une
 * complexité totale de Θ(n), et non Θ(n²).
 */

typedef struct dynarray {
  size_t max_size;
  size_t size;
  int *items;
} dynarray_t;

dynarray_t create_dynarray() {
  // On va doubler la taille plus tard, donc on ne veut jamais 0 (2*0 == 0 !)
  int *items = (int *) malloc(sizeof(int));
  dynarray_t array = { 1, 0, items };
  return array;
}

void free_dynarray(dynarray_t *array) {
  free(array->items);
}

/* Agrandit le tableau interne, sans changer le contenu logique.
 * Utilisé par dynarray_add quand on n'a plus de place.
 */
void dynarray_grow(dynarray_t *array) {
  size_t new_max_size = array->max_size * 2;

  int *new_items = (int *) malloc(new_max_size * sizeof(int));

  // Recopier les éléments existants
  for (size_t i = 0; i < array->size; i++) {
    new_items[i] = array->items[i];
  }

  // Pour être safe, initialiser le reste à 0.
  for (size_t i = array->size; i < new_max_size; i++) {
    new_items[i] = 0;
  }

  free(array->items);
  array->max_size = new_max_size;
  array->items = new_items;
  // size ne change pas. On n'a pas touché à la taille logique du tableau.
}

void dynarray_add(dynarray_t *array, int value) {
  // Agrandir si on n'a plus de place.
  if (array->size == array->max_size)
    dynarray_grow(array);

  // Stocker le nouvel élément, puis augmenter la taille logique
  array->items[array->size] = value;
  array->size++;
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
  array->size = new_size;
}

/* !!! Remarquez qu'à partir d'ici, on n'a *rien* changé par rapport à la
 * solution "naïve" ! C'est l'intérêt d'avoir fait des fonctions séparées pour
 * toutes les fonctionnalités "de base".
 */

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
