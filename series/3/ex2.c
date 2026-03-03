#include <stdio.h>
#include <math.h>

long double factorial (int n) {
	long double p = 1;
	for ( int a = n; a >= 2; a-- ) {
		p *= a;
	}
	return p;
}

long double cos_appr (double t, int n_max) {
	long double cost = 0;
	for ( int i = 0; i <= n_max; i++ ) {
		long double sn = pow(-1, i)*pow(t, 2*i)/factorial(2*i);
		cost += sn;
	}
	return cost;
}

int main () {
	printf("cos: ");
	double t;
	scanf("%lf", &t);
	printf("n: ");
	int n_max;
	scanf("%d", &n_max);
	printf("%.10Lf\n", cos_appr(t, n_max));
// 	printf("%.50lf\n", cos(t));
//	printf("0.33423772712450259823954724549766445375777963904487832589028365018123337244624616767207604888497932231039521843736550297381593875856462447945174949500262589165751897136880626807587503984543436091521914");
	return 0;
}
