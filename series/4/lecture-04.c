#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int read_int() {
  int x;
  scanf("%d", &x);
  return x;
}

int a = 5; // INTERDIT
const int b = 65;
const double pi = 3.141595653789;

void affiche(int xs[], size_t n) {
  for (size_t i = 0; i < n; i++) {
    printf("%d, ", xs[i]);
  }
  printf("\n");
}

void demander_tableau(int xs[], size_t n) {
  for (size_t i = 0; i < n; i++) {
    xs[i] = read_int();
  }
}

int main() {
  const int nombre = 5;

  int notes[5];
  notes[0] = 89;
  notes[1] = 75;
  notes[2] = 26;
  notes[3] = 89;
  notes[4] = 75;

  int notes2[] = { 89, 75, 26, 89, 75 };

  int somme = 0;
  for (size_t i = 0; i < nombre; i++) {
    somme += notes[i];
  }

  double moyenne = (double) somme / (double) nombre;

  printf("moyenne = %g\n", moyenne);


  for (size_t i = 0; i < nombre; i++) {
    printf("%d, ", notes[i]);
  }
  printf("\n");

  size_t n = (size_t) read_int();
  int tableau[n];
  for (size_t i = 0; i < n+3; i++) { // DANGER + 3
    tableau[i] = read_int();
  }

  double des_doubles[6];

  return 0;
}

