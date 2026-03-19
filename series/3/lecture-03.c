#include <stdio.h>
#include <stdbool.h>
#include <math.h>

//double compute_delta(double p, double q, double r);

// Soit f(x) = x²,  R -> R
double square(double x) {
  return x * x;
}

// Soit compute_delta (R, R, R) -> R
double compute_delta(double p, double q, double r) {
  return q*q - 4*p*r;
}

int read_pos_int() {
  int x = -1;

  while (x < 0) {
    scanf("%d", &x);
  }

  return x;
}

int read_pos_int2() {
  int x;

  do {
    scanf("%d", &x);
  } while (x < 0);

  return x;
}

double read_double() {
  double x;
  scanf("%lf", &x);
  return x;
}

int main() {
  int n = read_pos_int2();

  for (int i = 1; i <= 10; i++) {
    printf("%d x %d = %d\n", i, n, i * n);
  }

  int i = 1;
  while (i <= 10) {
    printf("%d x %d = %d\n", i, n, i * n);
    i++; // i = i + 1
  }

  i = i + 1;
  i += 1;
  i++;

  // i in [0, n[
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += i;
  }
  printf("somme = %d\n", sum);
  int moyenne = sum / n;

  int reste_division = 87 / 3; // 2, reste de la division euclidienne

  // len([a, b[) = b - a

  for (double x = 1.0; x <= 2.0; x += 0.1) {

  }

  // conversions

  int p = 5;
  double q = (double) p; // convertir un int en double

  double r = 5.6;
  int s = (int) round(r); // 5.6 -> 5  ---   -7.3 -> -7
  r = (int) r;

  printf("entrez a: ");
  double a = read_double();
  printf("entrez b: ");
  double b = read_double();
  printf("entrez c: ");
  double c = read_double();

  // ax² + bx + c = 0 ?
  double delta = compute_delta(a, b, c);
  if (delta == 0.0) {
    // une seule solution
    double x1 = -b / (2*a);
    printf("une solution: %g\n", x1);
  } else if (delta > 0.0) {
    // deux solutions
    double x1 = (-b + sqrt(delta)) / (2*a);
    double x2 = (-b - sqrt(delta)) / (2*a);
    printf("deux solutions: %g et %g\n", x1, x2);
  } else {
    printf("pas de solution\n");
  }

  return 0;
}

