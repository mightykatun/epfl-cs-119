#include <stdio.h>


int main() {
	int BASE = 4;

	double quantities[] = {
		800.0, // fromage
		2.0, // vin
		2.0, // ail
		400.0 // pain
	};

	char ingredients[4][15] = {
		"Fromage [g]",
		"Vin blanc [dl]",
		"Ail [#]",
		"Pain [g]"
	};

	int n; // nombre de convives
	printf("Nombre de personnes: ");
	scanf("%d", &n);

	printf("Pour %d personnes\n", n);

	for (int i = 0; i < 4; i++) {
        quantities[i] = quantities[i] * n / BASE;
		printf("\t%s : %.1f\n", ingredients[i], quantities[i]);
    }

	return 0;
}
