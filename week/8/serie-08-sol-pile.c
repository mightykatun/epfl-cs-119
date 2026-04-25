#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct stack {
  size_t max_stack_size;
  size_t stack_size;
  int *items;
} stack_t;

stack_t create_stack(size_t max_stack_size) {
  int *items = (int *) malloc(max_stack_size * sizeof(int));
  stack_t stack = { max_stack_size, 0, items };
  return stack;
}

void free_stack(stack_t *stack) {
  free(stack->items);
}

bool push(stack_t *stack, int elem) {
  if (stack->stack_size < stack->max_stack_size) {
    // On a encore de la place ; on peut empiler l'élément
    stack->items[stack->stack_size] = elem;
    stack->stack_size++;
    return true;
  } else {
    // Il n'y a plus de place ; on ne touche à rien et on renvoie false
    return false;
  }
}

bool pop(stack_t *stack, int *elem) {
  if (stack->stack_size > 0) {
    // Il y a au moins un élément dans la pile
    stack->stack_size--; // ici on décrémente d'abord stack_size
    *elem = stack->items[stack->stack_size];
    return true;
  } else {
    // La pile est vide ; on ne touche à rien et on renvoie false
    return false;
  }
}

bool equalstr(const char s1[], const char s2[]) {
  size_t i = 0;
  while (s1[i] != '\0' && s2[i] != '\0') {
    if (s1[i] != s2[i]) {
      return false;
    }
    i++;
  }

  /* Si on est arrivé au bout d'une des chaînes, alors on vérifie qu'on est
   * bien aussi au bout de l'autre chaîne.
   */
  return s1[i] == '\0' && s2[i] == '\0';
}

int main() {
  /* D'abord lire la première ligne, qui contient notamment la hauteur maximale
   * de la pile.
   */
  size_t max_stack_size;
  scanf("%lu", &max_stack_size);
  size_t instruction_count;
  scanf("%lu", &instruction_count);

  // On peut maintenant créer la pile elle-même
  stack_t stack = create_stack(max_stack_size);

  // Maintenant on lit les instructions
  for (size_t i = 0; i < instruction_count; i++) {
    // Lire le premier mot
    char instruction[100];
    scanf("%s", instruction); // pas de & ici car on lit une chaîne

    if (equalstr(instruction, "push")) {
      // Aussi lire l'élément à ajouter à la pile
      int elem;
      scanf("%d", &elem);

      // Tenter de l'ajouter ; en cas d'échec, afficher le message demandé
      if (!push(&stack, elem)) {
        printf("Étape %lu : pile remplie\n", i);
      }
    } else if (equalstr(instruction, "pop")) {
      // Tenter de retirer un élément
      int elem;
      if (pop(&stack, &elem)) {
        printf("%d\n", elem);
      } else {
        printf("Étape %lu : pile vide\n", i);
      }
    } else {
      // Uh oh ; on ne connaît pas cette instruction (pas demandé dans l'énoncé)
      printf("Étape %lu : instruction inconnue '%s'\n", i, instruction);
    }
  }

  // On n'oublie pas de libérer la stack !
  free_stack(&stack);

  return 0;
}
