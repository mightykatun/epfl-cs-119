#include <stdio.h>
#include <math.h>

int main () {
	int integers[] = {
		5, 3, 65, 17, 2, 5, 3
	};

	int length = sizeof(integers) / sizeof(*integers);

	int product = 1;

	for ( size_t i = 0; i < length; i++ ) { // size_t is an unsigned integer in case your table is bigger than 4 billion elements or so (int limit)
		int num = integers[i];
		printf("%d\n", num);
		product *= num;
	}
	
	printf("p = %d\n", product);
	
	double doubles[length];
	double sum = 0;

	for ( size_t i = 0; i < length; i++ ) {
		double num = log(integers[i]);
		doubles[i] = num;
		sum += num;
	}

	printf("s = %.10f\n", sum);
	printf("e^s = %.10f", exp(sum));

	return 0;
}
