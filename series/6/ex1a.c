#include <stdio.h>

int plus10(int a) {
	a += 10;
	printf("plus 10 = %d\n", a);
	return a;
}

int main() {
	int v = 5;
	printf("v = %d\n", v);
	plus10(plus10(v));
	printf("v = %d\n", v);
}
