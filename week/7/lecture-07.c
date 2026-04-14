#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

typedef struct player {
  char name[100];
  int level;
  bool has_shield;
} player_t;

//typedef struct player player_t; // alias "player_t" veut dire "struct player"

void show_player(const player_t *p) {
  printf("%s, niveau %d, avec bouclier: %d\n",
      p->name, p->level, p->has_shield);
}

void inc_level(player_t *p) {
  (*p).level += 1;
  p->level += 1; // équivalent à au-dessus
}

void foo(int xs[]) {

}

int main() {
  printf("Lecture 7\n");

  player_t p;
  strncpy(p.name, "Link", 100);
  p.level = 1;
  p.has_shield = false; // tableau[i]

  int *p_level = &p.level;

  player_t players[10];
  show_player(&players[0]);

  inc_level(&players[0]);

  int bar[5];
  foo(bar);

  return 0;
}

