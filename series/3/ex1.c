#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isdivisible (int a, int b) {
	if ( (a / b * b) == a ) {
		return true;
	}
	return false;
}

bool isprime (int p) {
	if ( p < 2 ) {
		return false;
	}
	int s = floor(sqrt(p));
	for ( int b = 2; b <= s; b++ ) {
		if ( isdivisible(p, b) ) {
			return false;
		}
	}
	return true;
}


int main () {
//	printf("a: ");
//	int a;
//	scanf("%d", &a);
//	printf("b: ");
//	int b;
//	scanf("%d", &b);
	printf("check primality: ");
	int p;
	scanf("%d", &p);
	if ( isprime(p) ) {
		printf("True\n");
		return 0;
	}
	printf("False\n");
	return 0;
}
