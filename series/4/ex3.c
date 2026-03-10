#include <stdio.h>
#include <stdbool.h>


bool next (int* code, int len) {
	for (int i = len - 1; i >= 0; i--) {
		if (code[i] <= 5) {
			code[i]++;
			return true;
		}
		if (code[i] == 6) {
			code[i] = 0;
			continue;
		}
	}
	return false;
}

int show (int* code, int len) {
	for (int i = 0; i < len; i++) {
		printf("%d", code[i]);
	}
	printf("\n");
	return 0;
}

int main() {
	printf("Amount of digits: ");
	int num;
	scanf("%d", &num);
	int code[num];

	for (int i = num - 1; i >= 0; i--) {
		code[i] = 0;
	}

	bool has_next = true;
	while (has_next) {
		show(code, num);
		has_next = next(code, num);
	}
	return 0;
}
