#include <stdio.h>

int* ptr_plus10(int *a) {
	*a += 10;
	printf("plus 10 = %d\n", *a);
	return a;
}

int main() {
	int v = 5;
	printf("v = %d\n", v);
	ptr_plus10(ptr_plus10(&v));
	printf("v = %d\n", v);
}
