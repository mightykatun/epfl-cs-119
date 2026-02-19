#include <stdio.h>

int main() {
	printf("Année de naissance: ");
	int birth;
	scanf("%d", &birth);
	int age = 2026 - birth;
	printf("%d\n", age);
	return 0;
}
