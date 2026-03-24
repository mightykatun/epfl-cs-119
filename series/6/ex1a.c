#include <stdio.h>

int plus10(int a) { // function plus10 takes an integer a as argument
	a += 10; // adds 10 to a, a is local to this function
	printf("plus 10 = %d\n", a); // displays the value of the local a after adding 10
	return a;
}

int main() {
	int v = 5;
	printf("v = %d\n", v); // will print the initial value of v, which is 5
	plus10(plus10(v)); // calls plus10(5), which will print 15, return 15, then calls plus10(15), which will print 25, return 25, but the return value is not useded or us
	printf("v = %d\n", v); // prints the value of v which is still 5
}

// predicted output:
//
// v = 5
// plus10 = 15
// plus10 = 25
// v = 5
