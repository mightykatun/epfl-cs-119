#include <stdio.h>
#include <math.h>

int main () {
	int integers[] = {
		5, 3, 65, 17, 2, 5, 3
	};

	int length = sizeof(integers) / sizeof(integers[0]);

	int product = 1;

	for ( int i = 0; i < length; i++ ) {
		int num = integers[i];
		printf("%d\n", num);
		product *= num;
	}
	
	printf("p = %d\n", product);
	
	double doubles[length];
	double sum = 0;

	for ( int i = 0; i < length; i++ ) {
		double num = log(integers[i]);
		doubles[i] = num;
		sum += num;
	}

	printf("s = %.10f\n", sum);
	printf("e^s = %.10f", exp(sum));

	return 0;
}
