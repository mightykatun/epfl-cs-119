#include <stdio.h>
#include <time.h>

int main() {
	time_t seconds = time(NULL);
    struct tm* current_time = localtime(&seconds); 
    int year = current_time -> tm_year + 1900;
	
	printf("Année de naissance: ");
	int birth;
	scanf("%d", &birth);
	
	int age = year - birth;
	printf("Age: %d\n", age);
	return 0;
}
