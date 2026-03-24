#include <stdio.h>

void cycle(int *a, int *b, int *c) { // equivalent to cycle(int* a, int* b, int* c)
	int temp = *a;
	*a = *b;
	*b = *c;
	*c = temp;
}

int main() {
	int x = 5, y = 7, z = 17;
	cycle(); // à vous de transmettre x, y, z pour les paramètres a, b, c
	printf("%d %d %d\n", x, y, z);
}
