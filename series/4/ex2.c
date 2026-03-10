#include <stdio.h>

double scalar (double* vec1, double* vec2, int n) {
	double res = 0;
	for (int i = 0; i < n; ++i)
		res += vec1[i]*vec2[i];
	return res;
}


int main () {
	double a[] = {5, 3, 65, 17, 2, 5, 3};
	double b[] = {4, 61, 456, 12, 3, 1, 5};
	double c[] = {8, 45, 3, 4};
	double d[] = {89, 4, 74, 1};

	
	printf("a*b = %.0f\n", scalar(a, b, 7));
	printf("c*d = %.0f\n", scalar(c, d, 4));
	
	return 0;
}

