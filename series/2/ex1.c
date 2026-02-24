#include <stdio.h>

int main () {
	double lower_bound = 3.567;
	double upper_bound = 9.768;

	printf("Enter a real number: ");
	double input;
	scanf("%lf", &input);
	
	if (input >= lower_bound && input <= upper_bound) {
		printf("%f is in the interval [%f, %f]", input, lower_bound, upper_bound);	
	} else {
		printf("%f is not in the interval [%f, %f]", input, lower_bound, upper_bound);
	}

	return 0;
}
