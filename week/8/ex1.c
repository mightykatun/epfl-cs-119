#include <stdio.h>
#include <stdlib.h>

double* inverse (const size_t n) {
	double* inverse_array = (double*) malloc(n * sizeof(double));
	for (size_t i=1; i<n+1; i++) inverse_array[i] = 1.0 / ((double) i);
	return inverse_array;
}

int main () {
	// requests n from user
	// calls inverse and prints the result
	size_t n;
	printf("Enter n: ");
	scanf("%zu", &n);
	double* result = inverse(n);
	for (size_t i=0; i<n; i++) printf("%.9f ", result[i]);
	free(result);
	return 0;
}
