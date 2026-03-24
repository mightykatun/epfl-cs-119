#include <stdio.h>

int* ptr_plus10(int *a) { // takes a pointer to an int and returns a pointer to an int
	*a += 10; // adds 10 to the value of a (external variable)
	printf("plus10 = %d\n", *a); // prints the the variable a after having added 10 to it
	return a; // returns the pointer to the variable a
}

int main() {
	int v = 5; // declares an integer variable v and initializes it to 5
	printf("v = %d\n", v); // prints the value of v
	ptr_plus10(ptr_plus10(&v)); // calls ptr_plus10 with the pointer to v: &v, then returns the same pointer to v after having added 10 to v's value
	printf("v = %d\n", v); // prints the value of v again, (added 10 twice -> +20)
}

// Predicted output:
//
// v = 5
// plus10 = 15
// plus10 = 25
// v = 25
