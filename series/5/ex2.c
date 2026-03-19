#include <stdio.h>
#include <stdbool.h>

bool is_substring (char* substring, char* string, int p) {
	int i = 0;
	while (substring[i] != '\0') {
		if (string[p++] != substring[i++]) {
			return false;
		}

	}
	return true;
}

int occurences (char* substring, char* string) {
	int i = 0;
	int count = 0;
	while (string[i] != '\0') {
		if (is_substring(substring, string, i)) count++;
		i++;
	}
	return count;
}

int main () {
	char string[100];
	char substring[100];
	printf("Enter a string: ");
	scanf("%s", string);
	printf("Enter a substring: ");
	scanf("%s", substring);
	printf("The substring occurs %d times in the string.\n", occurences(substring, string));
	return 0;
}
