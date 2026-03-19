#include <stdio.h>
#include <stdbool.h>
#include <math.h>

double compute_delta(double p, double q, double r);

// Soit compute_delta (R, R, R) -> R
double compute_delta(double p, double q, double r) {
  return q*q - 4*p*r;
}

int main() {
  printf("Hello\n");

  double x = 0.1;
  double y = 0.2;
  double z = x + y;

  bool a = x > 1.0;
  printf("a = %d\n", a);

  bool c = a || (x < -1.0); // a *ou* x < -1.0
  bool d = a && x < 10.0; // a *et* x < 10
  bool e = !d; // non d
  bool f = (c && !d) || (!c && d);

  bool p = (x != 0.0) & (1/x > 5.0);

  if (x < 1.0 && x > 0.0) {
    // branche vrai
    printf("x est petit positif\n");
  } else {
    // branche faux
    printf("x n'est pas petit positif\n");
  }

  bool vrai = true;
  bool faux = false;

  x = 0.5;
  printf("z = %f\n", z);
  printf("devant %f derrière %d et %d", x, 10, 15);
  printf("%.17f\n", z);

  double a2 = 1.0;
  printf("entrez a: ");
  // demande un double à l'utilisateur/utilisatrice
  // et le stocke dans a2
  scanf("%lf", &a2);
  // pour un int, utiliser %d

  double b2 = 4.0;
  double c2 = -15.0;

  // ax² + bx + c = 0 ?
  double delta = compute_delta(a2, b2, c2);
  if (delta == 0.0) {
    // une seule solution
    double x1 = -b2 / (2*a2);
    printf("une solution: %g\n", x1);
  } else if (delta > 0.0) {
    // deux solutions
    double x1 = (-b2 + sqrt(delta)) / (2*a2);
    double x2 = (-b2 - sqrt(delta)) / (2*a2);
    printf("deux solutions: %g et %g\n", x1, x2);
  } else {
    printf("pas de solution\n");
  }

  return 0;
}

