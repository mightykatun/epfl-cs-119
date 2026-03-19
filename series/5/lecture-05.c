#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

int read_int() {
  int x;
  scanf("%d", &x);
  return x;
}

size_t my_strlen_modif(char str[]) {
  size_t i = 0;
  while (str[i] != '\0') {
    str[i] = 'A';
    i++;
  }
  return i;
}

size_t my_strlen(const char str[]) {
  // my_strlen_modif(str); // warning, mais à considérer comme error
  size_t i = 0;
  while (str[i] != '\0') {
    // str[i] = 'A'; // error
    i++;
  }
  return i;
}

int main() {
  printf("Lecture 5\n");

  const double pi = 3.14;

  const char hello[] = { 'h', 'e', 'l', 'l', 'o', '\0' };
  const char hello2[] = "hello"; // équivalent
  //hello[1] = 'A';

  printf(hello);
  printf("\n");

  char text[100];
  strncpy(text, hello, 100);
  strncat(text, hello2, 50);
  printf(text);
  printf("\n");
  printf("%d\n", (int) strlen(text));
  printf("%d\n", (int) my_strlen(text));

  // Lire une chaîne de caractères entière depuis le clavier
  // Attention, elle contiendra le \n final + le \0 après celui-ci
  fgets(text, 100, stdin);

  char c = 'B';

  return 0;
}
