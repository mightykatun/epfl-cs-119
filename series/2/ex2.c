#include <stdio.h>
#include <math.h>

char* func_1 (double x) {
	
	static char message[100];
	char f_name[] = "Function 1";
	
	// x/(1-exp(x)) undefined at x = 0
	int problem_val_1 = 0;
	
	// check problem value x = 0
	if (x == problem_val_1) {
		snprintf(message, sizeof(message), "%s: undefined at x=%.0f", f_name, x); 
		return message;
	}
	// return f(x)
	else {
		double result = x / (1- exp(x)); 
		snprintf(message, sizeof(message), "%s: f(%.3f)=%.3f", f_name, x, result);
		return message;
	}
}

char* func_2 (double x) {
	
	static char message[100];
	char f_name[] = "Function 2";
	
	// log(x) undefined if x <= 0
	int problem_val_1 = 0;
	// 2/(x-1) undefined if x = 1
	int problem_val_2 = 1;
	
	// check if x <= 0 or x = 1
	if (x <= problem_val_1 || x == problem_val_2) {
		snprintf(message, sizeof(message), "%s: undefined at x=%.0f", f_name, x); 
		return message;
	}
	// return f(x)
	else {
		double result = x * log(x) * exp(2 / (x - 1)); 
		snprintf(message, sizeof(message), "%s: f(%.3f)=%.3f", f_name, x, result);
		return message;
	}
}

char* func_3 (double x) {
	
	static char message[100];
	char f_name[] = "Function 3";
	
	// (...)/(x - 2) undefined at x = 2
	int problem_val_1 = 2;
	// sqrt(x^2-8x) defined if x^2-8x >= 0 -> undefined if x in ]0;8[
	int problem_interval_lo = 0;
	int problem_interval_hi = 8;
	
	// check problem values
	if (x == problem_val_1 || (x > problem_interval_lo && x < problem_interval_hi)) {
		snprintf(message, sizeof(message), "%s: undefined at x=%.0f", f_name, x); 
		return message;
	}
	// return f(x)
	else {
		double result = (-x-sqrt(pow(x, 2)-8*x))/(2-x); 
		snprintf(message, sizeof(message), "%s: f(%.3f)=%.3f", f_name, x, result);
		return message;
	}
}

// shortcut for the inside of function 4
double m_expr_4 (double x) {
	return (sin(x)-x/20)*log(pow(x, 2)-1/x);
}

char* func_4 (double x) {

	static char message[100];
	char f_name[] = "Function 4";
	
	// log(x^2-1/x) is undefined in ]0;1[
	int problem_int_log_lo = 0; 
	int problem_int_log_hi = 1; 

	// first check if the log part is defined
	if (x > problem_int_log_lo && x < problem_int_log_hi) {
		snprintf(message, sizeof(message), "%s: undefined at x=%.0f", f_name, x); 
		return message;
	}
	// if the log part is defined, check if the square root will be defined
	else if (m_expr_4(x) < 0) {
		snprintf(message, sizeof(message), "%s: undefined at x=%.0f", f_name, x); 
		return message;
	}
	// if the square root is defined, return f(x)
	else {
		double result = sqrt(m_expr_4(x));
		snprintf(message, sizeof(message), "%s: f(%.3f)=%.3f", f_name, x, result);
		return message;
	}
}

// user input and run all four functions
int main () {
	printf("Enter a real number: ");
	double input;
	scanf("%lf", &input);
	
	printf("i\n%s\n", func_1(input));
	printf("%s\n", func_2(input));
	printf("%s\n", func_3(input));
	printf("%s\n", func_4(input));
}
