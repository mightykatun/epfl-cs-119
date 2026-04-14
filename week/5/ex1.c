#include <stdio.h>

int len_str_1 (char* string) { 
	int i = 0; 
	char character = *string; 
	while (character != '\0') { 
		i += 1;
		character = string[i]; 
	}
	return i;
}

int len_str_2 (char* string) {
	int i = -1;
	while (string[++i]);
	return i;
}


int main () {
	char string[100];
	printf("Enter a string: ");
	scanf("%s", string);
	int length_1 = len_str_1(string);
	int length_2 = len_str_2(string);
	printf("The length of the string (method 1) is: %d\n", length_1);
	printf("The length of the string (method 2) is: %d\n", length_2);
	return 0;
}
