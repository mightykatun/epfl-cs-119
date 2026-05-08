// --- ORIGINAL INCLUDES ---
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

// --- ADDED INCLUDES ---
#include <string.h>

// --- NE PAS MODIFIER A PARTIR D'ICI ---

/* Structure pour le contenu "brut" lu depuis le fichier de carte.
 * La carte est de taille (width x height).
 * La position initiale de Bix est (posx, posy), indices basés sur 0.
 *
 * map_lines est un tableau de `height` chaînes de caractères.
 *
 * Attention, les lignes sont dans l'ordre d'apparition du fichier. Donc
 * l'indice 0 est la ligne tout en haut, qui devrait avoir l'ordonnée
 * `height - 1` dans la carte.
 *
 * Deuxième attention : la longueur des lignes peut être plus courte que
 * `width`. Si elle est plus courte, il faut supposer que des espaces (donc du
 * "sol") se trouve au-delà de la fin de la chaîne de caractères.
 *
 * Troisième attention : rien ne dit que les lignes elles-mêmes soient
 * correctes. Peut-être qu'elles contiennent des caractères invalides.
 */
typedef struct rawmap {
  size_t width;
  size_t height;
  int posx;
  int posy;
  char **map_lines; // an array of strings
} rawmap_t;

/* Crée une carte brute à partir d'un contenu constant.
 * C'est utile pour la carte par défaut, mais surtout pour vos tests unitaires.
 * Utilisez cette fonction dans vos tests unitaires pour obtenir une carte de
 * base que vous pouvez tester.
 * Regardez `make_default_rawmap()` pour savoir comment utiliser cette fonction.
 */
rawmap_t make_rawmap(size_t width, size_t height, int posx, int posy, const char *lines[]) {
  rawmap_t map;
  map.width = width;
  map.height = height;
  map.posx = posx;
  map.posy = posy;

  // Allocate the array of line strings
  map.map_lines = (char **) calloc(map.height, sizeof(char *));

  // Read map.height lines
  for (size_t line_index = 0; line_index < map.height; line_index++) {
    const char *line = lines[line_index];
    size_t len = strlen(line);
    map.map_lines[line_index] = (char *) calloc(len + 1, sizeof(char));
    strncpy(map.map_lines[line_index], line, len);
  }

  return map;
}

/* Fonction interne qui signale une erreur de format majeure dans le fichier.
 * Ne pas appeler cette fonction vous-même. Elle est appelée par `read_map_file`.
 */
void error_bad_map_file(FILE *f, char **lines, size_t line_count, size_t line_no) {
  if (lines != NULL) {
    for (size_t i = 0; i < line_count; i++)
      free(lines[i]);
    free(lines);
  }

  fclose(f);

  printf("Erreur de format dans le fichier à la ligne %lu\n", line_no);
  exit(1);
}

/* Lit le contenu d'un fichier de carte de manière "brute".
 * Si un argument a été donné au programme (avec `./puzzle <fichier-carte.txt>`)
 * alors c'est le fichier <fichier-carte.txt> qui est lu. Sinon, par défaut
 * c'est le fichier `default-map.txt` qui est lu (très utile si vous devez
 * déboguer votre programme, car c'est ce fichier qui sera alors lu).
 *
 * Le résultat est une `rawmap_t`. Voir sa documentation pour le contenu. Il
 * doit être libéré avec `free_rawmap`.
 *
 * En cas d'erreur de lecture majeure (qui ne permettrait pas de construire une
 * rawmap_t valable), un message est affiché à l'écran et le programme est
 * immédiatement arrêté. Le code qui appelle read_map_file sait donc que le
 * rawmap_t renvoyé est valable.
 */
rawmap_t read_map_file(const char *file_name) {
  // Open the file
  FILE *map_file = fopen(file_name, "r");
  if (map_file == NULL) {
    printf("On dirait que le fichier '%s' n'existe pas.\n", file_name);
    exit(1);
  }

  rawmap_t map;

  // Read width, height, posx and posy
  if (fscanf(map_file, "%lu %lu", &map.width, &map.height) < 2)
    error_bad_map_file(map_file, NULL, 0, 1);
  if (fscanf(map_file, "%d %d", &map.posx, &map.posy) < 2)
    error_bad_map_file(map_file, NULL, 0, 2);

  size_t line_buf_len = map.width + 2; // 1 for \n and 1 for \0
  char line[line_buf_len];
  memset(line, 0, line_buf_len); // just in case any of the fgets fails

  // Throw away the rest of the line after the second fscanf
  if (fgets(line, line_buf_len, map_file) == NULL)
    error_bad_map_file(map_file, NULL, 0, 2);

  // Allocate the array of line strings
  map.map_lines = (char **) calloc(map.height, sizeof(char *));

  // Read map.height lines
  for (size_t line_index = 0; line_index < map.height; line_index++) {
    if (fgets(line, line_buf_len, map_file) == NULL)
      error_bad_map_file(map_file, map.map_lines, line_index, 3 + line_index);
    size_t len = strlen(line);
    if (len == 0 || line[len - 1] != '\n')
      error_bad_map_file(map_file, map.map_lines, line_index, 3 + line_index);
    map.map_lines[line_index] = (char *) calloc(len + 1, sizeof(char));
    strncpy(map.map_lines[line_index], line, len);
  }

  fclose(map_file);

  return map;
}

void free_rawmap(rawmap_t *map) {
  for (size_t i = 0; i < map->height; i++)
    free(map->map_lines[i]);
  free(map->map_lines);
}

// --- FIN DE LA ZONE A NE PAS MODIFIER - ECRIVEZ VOTRE PROGRAMME CI-DESSOUS ---

/* Crée la carte brute par défaut, si on ne donne pas de nom de fichier au
 * programme.
 *
 * La carte doit être libérée avec free_rawmap.
 */
rawmap_t make_default_rawmap() {
  /* Vous pouvez modifier cette carte par défaut si vous voulez.
   * N'hésitez pas à imiter cette fonction pour créer facilement des cartes
   * dans vos tests unitaires !
   */
  const char *lines[] = {
    "xxxxxxxxxx",
    "x     +! x",
    "x  oo    x",
    "x        x",
    "x    *   x",
    "x  x * + x",
    "x  x     x",
    "x        x",
    "x        x",
    "xxxxxxxxxx",
  };
  return make_rawmap(10, 10, 1, 1, lines);
}

// --- HELPER FUNCTIONS & VARIABLES ---

/* cell type */
typedef enum { FLOOR, FIXED, HOLE, GOAL, MOVABLE, ONE_MOVE, MOVABLE_ON_GOAL } cell_t;

/* game state: array indexed by [y * width + x] with y=0 the bottom row */
typedef struct {
  int width;
  int height;
  int posx, posy;   /* position of Bix */
  cell_t *cells;    /* width * height cells */
} game_t;

/* convert a map character to cell type */
cell_t char_to_cell(char c) {
  switch (c) {
    case 'x': return FIXED;
    case 'o': return HOLE;
    case '!': return GOAL;
    case '*': return MOVABLE;
    case '+': return ONE_MOVE;
    default:  return FLOOR;
  }
}

/* is bix in the field? */
bool in_bounds(game_t *g, int x, int y) {
  return x >= 0 && x < g->width && y >= 0 && y < g->height;
}

/* (x,y) to array index */
int cell_index(game_t *g, int x, int y) {
  return y * g->width + x;
}

/* get cell type at (x,y), FIXED if out of bounds (border) */
cell_t get_cell(game_t *g, int x, int y) {
  if (!in_bounds(g, x, y)) return FIXED;
  return g->cells[cell_index(g, x, y)];
}

/* check if cell free (Bix or block can move there) */
bool cell_is_free(game_t *g, int x, int y) {
  cell_t c = get_cell(g, x, y);
  return c == FLOOR || c == HOLE || c == GOAL;
}

/* return the display character for cell (x,y) -> overlay Bix */
char cell_char(game_t *g, int x, int y) {
  if (x == g->posx && y == g->posy) return '@';
  switch (get_cell(g, x, y)) {
    case FIXED:          return 'x';
    case HOLE:           return 'o';
    case GOAL:           return '!';
    case MOVABLE:        return '*';
    case MOVABLE_ON_GOAL: return '*';
    case ONE_MOVE:       return '+';
    default:             return ' ';
  }
}

// --- MAP DATA HANDLING FUNCTIONS ---

/* get raw character at gamew (x,y) from rawmap + "padding" with spaces */
char rawmap_char_at(rawmap_t *rm, int x, int y) {
  int line_idx = (int)rm->height - 1 - y;
  char *line = rm->map_lines[line_idx];
  int len = (int)strlen(line);
  /* ignore "\n" for length check */
  if (len > 0 && line[len - 1] == '\n') len--;
  if (x >= len) return ' ';
  return line[x];
}

/* create game_t from rawmap_t, build the cell array */
game_t make_game(rawmap_t *rm) {
  game_t g;
  g.width = (int)rm->width;
  g.height = (int)rm->height;
  g.posx = rm->posx;
  g.posy = rm->posy;
  int n = g.width * g.height; /* number of cells used for calloc */
  g.cells = (cell_t *)calloc(n, sizeof(cell_t));
  for (int y = 0; y < g.height; y++) {
    for (int x = 0; x < g.width; x++) {
      g.cells[cell_index(&g, x, y)] = char_to_cell(rawmap_char_at(rm, x, y));
    }
  }
  return g;
}

/* FREEDOM! */
void free_game(game_t *g) {
  free(g->cells);
  g->cells = NULL;
}

/* reasign rawmap to reset */
void reset_game(game_t *g, rawmap_t *rm) {
  free_game(g);
  *g = make_game(rm);
}

// --- DISPLAY FUNCTION ---

/* print the current game state -> top row (y=height-1) first */
void display_game(game_t *g) {
  for (int y = g->height - 1; y >= 0; y--) {
    for (int x = 0; x < g->width; x++) {
      putchar(cell_char(g, x, y));
    }
    putchar('\n');
  }
}

// --- GAME LOGIC FUNCTIONS ---

/* attempt to move Bix by (dx,dy) -> handle pushing blocks, falling in holes
 * raeching goal -> sets *won = true
 * resets game if Bix falls in hole */
void move_bix(game_t *g, rawmap_t *rm, int dx, int dy, bool *won) {
  int nx = g->posx + dx; /* new x */
  int ny = g->posy + dy; /* new y */
  cell_t target = get_cell(g, nx, ny);

  if (cell_is_free(g, nx, ny)) {
    /* move Bix to (nx, ny) */
    g->posx = nx;
    g->posy = ny;
    if (target == HOLE) {
      reset_game(g, rm);
    } else if (target == GOAL) {
      *won = true; /* the variale won lives in the caller func */
    }
    return;
  }

  /* check if there is a pushable block at (nx, ny) */
  if (target != MOVABLE && target != ONE_MOVE && target != MOVABLE_ON_GOAL) return;

  /* position behind the block */
  int bx = nx + dx;
  int by = ny + dy;
  if (!cell_is_free(g, bx, by)) return;  /* can't push */

  int idx_block = cell_index(g, nx, ny); /* where the block currently is */
  int idx_dest = cell_index(g, bx, by);
  cell_t dest = g->cells[idx_dest];

  /* remove block from current position -> floor */
  g->cells[idx_block] = (target == MOVABLE_ON_GOAL) ? GOAL : FLOOR;

  /* place block at destination */
  if (dest == HOLE) {
    /* block falls in hole and hole stays */
  } else if (target == ONE_MOVE) {
    /* one-move block becomes fixed terrain */
    g->cells[idx_dest] = FIXED;
  } else {
    /* place movable block ! moaybe on goal */
    g->cells[idx_dest] = (dest == GOAL) ? MOVABLE_ON_GOAL : MOVABLE;
  }

  /* move Bix to where the block was */
  g->posx = nx;
  g->posy = ny;

  /* if we uncovered a goal -> Bix is on it */
  if (g->cells[idx_block] == GOAL) {
    *won = true;
  }
}

/* apply a single command character -> announce through pointers
 * whether the game was won or the player quit */
void apply_command(game_t *g, rawmap_t *rm, char cmd, bool *won, bool *quit) {
  switch (cmd) {
    case 'e': move_bix(g, rm,  0,  1, won); break; /* up */
    case 'd': move_bix(g, rm,  0, -1, won); break; /* down */
    case 's': move_bix(g, rm, -1,  0, won); break; /* left */
    case 'f': move_bix(g, rm,  1,  0, won); break; /* right */
    case 'r': reset_game(g, rm);            break;
    case 'x': *quit = true;                 break;
    default:                                break; /* ignore unknown characters */
  }
}

// --- GAME HANDLING FUNCTIONS ---

/* main game loop: display initial state, read and apply commands
 * display after each <- stop on win or quit */
void run_game(game_t *g, rawmap_t *rm) {
  /* initialize game state */
  bool won = false;
  bool quit = false;
  char line[256]; /* buffer for reading input lines */

  display_game(g);

  /* MAINLOOP */
  while (!won && !quit) {
    if (fgets(line, sizeof(line), stdin) == NULL) break; /* read a line of input, stop if EOF */
    for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++) { /* loop through command string until newline or end of string */
      apply_command(g, rm, line[i], &won, &quit); /* apply command, which may update won and quit */
      display_game(g);
      if (won || quit) break;
    }
  }

  if (won) {
    printf("Bravo ! Tu as atteint le goal !\n");
  } else {
    printf("Abandon :-(\n");
  }
}

// --- UNIT TESTS ---

/* test I: basic movement on open floor */
void test_basic_movement(void) {
  const char *lines[] = {
    "xxxxx",
    "x   x",
    "x   x",
    "x   x",
    "xxxxx",
  };
  rawmap_t rm = make_rawmap(5, 5, 2, 2, lines);
  game_t g = make_game(&rm);
  bool won = false;

  /* move right */
  move_bix(&g, &rm, 1, 0, &won);
  assert(g.posx == 3 && g.posy == 2 && !won);

  /* move up */
  move_bix(&g, &rm, 0, 1, &won);
  assert(g.posx == 3 && g.posy == 3 && !won);

  /* move left */
  move_bix(&g, &rm, -1, 0, &won);
  assert(g.posx == 2 && g.posy == 3 && !won);

  /* move down */
  move_bix(&g, &rm, 0, -1, &won);
  assert(g.posx == 2 && g.posy == 2 && !won);

  free_game(&g);
  free_rawmap(&rm);
}

/* test II: cannot walk through walls or outside the field */
void test_wall_block(void) {
  const char *lines[] = {
    "xxx",
    "x x",
    "xxx",
  };
  rawmap_t rm = make_rawmap(3, 3, 1, 1, lines);
  game_t g = make_game(&rm);
  bool won = false;

  move_bix(&g, &rm, 1, 0, &won);
  assert(g.posx == 1 && g.posy == 1);  /* blocked by wall */

  move_bix(&g, &rm, 0, 1, &won);
  assert(g.posx == 1 && g.posy == 1);  /* blocked by wall */

  free_game(&g);
  free_rawmap(&rm);
}

/* test III: push a movable block */
void test_push_movable(void) {
  const char *lines[] = {
    "xxxxx",
    "x   x",
    "x * x",
    "x   x",
    "xxxxx",
  };
  rawmap_t rm = make_rawmap(5, 5, 1, 2, lines);
  game_t g = make_game(&rm);
  bool won = false;

  /* push block right */
  move_bix(&g, &rm, 1, 0, &won);
  assert(g.posx == 2 && g.posy == 2);
  assert(get_cell(&g, 3, 2) == MOVABLE);
  assert(get_cell(&g, 2, 2) == FLOOR);

  free_game(&g);
  free_rawmap(&rm);
}

/* test IV: push a one-move block -> becomes fixed block */
void test_push_one_move(void) {
  const char *lines[] = {
    "xxxxx",
    "x   x",
    "x + x",
    "x   x",
    "xxxxx",
  };
  rawmap_t rm = make_rawmap(5, 5, 1, 2, lines);
  game_t g = make_game(&rm);
  bool won = false;

  /* push one-move block right */
  move_bix(&g, &rm, 1, 0, &won);
  assert(g.posx == 2 && g.posy == 2);
  assert(get_cell(&g, 3, 2) == FIXED); /* became fixed terrain */

  free_game(&g);
  free_rawmap(&rm);
}

/* test V: push a block into a hole -> block disappears and hole stays */
void test_push_into_hole(void) {
  const char *lines[] = {
    "xxxxx",
    "x   x",
    "x *ox",
    "x   x",
    "xxxxx",
  };
  rawmap_t rm = make_rawmap(5, 5, 1, 2, lines);
  game_t g = make_game(&rm);
  bool won = false;

  /* push block right into hole */
  move_bix(&g, &rm, 1, 0, &won);
  assert(g.posx == 2 && g.posy == 2);
  assert(get_cell(&g, 3, 2) == HOLE); /* block is gone, hole remains */

  free_game(&g);
  free_rawmap(&rm);
}

/* test VI: Bix falls in a hole -> game resets */
void test_bix_falls_in_hole(void) {
  const char *lines[] = {
    "xxxxx",
    "x   x",
    "x o x",
    "x   x",
    "xxxxx",
  };
  rawmap_t rm = make_rawmap(5, 5, 1, 2, lines);
  game_t g = make_game(&rm);
  bool won = false;

  /* move east into the hole */
  move_bix(&g, &rm, 1, 0, &won);
  /* should reset to initial position */
  assert(g.posx == 1 && g.posy == 2);
  assert(!won); /* falling in hole doesn't win the game */

  free_game(&g);
  free_rawmap(&rm);
}

/* test VII: Bix reaches the goal */
void test_win(void) {
  const char *lines[] = {
    "xxxxx",
    "x   x",
    "x ! x",
    "x   x",
    "xxxxx",
  };
  rawmap_t rm = make_rawmap(5, 5, 1, 2, lines);
  game_t g = make_game(&rm);
  bool won = false;

  move_bix(&g, &rm, 1, 0, &won);
  assert(g.posx == 2 && g.posy == 2);
  assert(won); /* should have won the game */

  free_game(&g);
  free_rawmap(&rm);
}

/* test VIII: cannot push a block if there is a wall behind it */
void test_push_blocked(void) {
  const char *lines[] = {
    "xxxxx",
    "x   x",
    "x *xx",
    "x   x",
    "xxxxx",
  };
  rawmap_t rm = make_rawmap(5, 5, 1, 2, lines);
  game_t g = make_game(&rm);
  bool won = false;

  move_bix(&g, &rm, 1, 0, &won);
  assert(g.posx == 1 && g.posy == 2); /* didn't move */
  assert(get_cell(&g, 2, 2) == MOVABLE);

  free_game(&g);
  free_rawmap(&rm);
}

/* test IX: cannot push two blocks at once */
void test_push_two_blocks(void) {
  const char *lines[] = {
    "xxxxxx",
    "x    x",
    "x ** x",
    "x    x",
    "xxxxxx",
  };
  rawmap_t rm = make_rawmap(6, 5, 1, 2, lines);
  game_t g = make_game(&rm);
  bool won = false;

  move_bix(&g, &rm, 1, 0, &won);
  assert(g.posx == 1 && g.posy == 2); /* didn't move: two blocks */
  assert(get_cell(&g, 2, 2) == MOVABLE);
  assert(get_cell(&g, 3, 2) == MOVABLE);

  free_game(&g);
  free_rawmap(&rm);
}

/* test X: reset command restores initial state */
void test_reset_command(void) {
  const char *lines[] = {
    "xxxxx",
    "x   x",
    "x * x",
    "x   x",
    "xxxxx",
  };
  rawmap_t rm = make_rawmap(5, 5, 1, 2, lines);
  game_t g = make_game(&rm);
  bool won = false;
  bool quit = false;

  /* move right (pushes block) */
  apply_command(&g, &rm, 'f', &won, &quit);
  assert(g.posx == 2 && g.posy == 2);

  /* reset */
  apply_command(&g, &rm, 'r', &won, &quit);
  assert(g.posx == 1 && g.posy == 2);
  assert(get_cell(&g, 2, 2) == MOVABLE); /* check if block is back */

  free_game(&g);
  free_rawmap(&rm);
}

/* test XI: incomplete map lines are padded with floor */
void test_incomplete_map(void) {
  const char *lines[] = {
    "xxx",
    "x",
    "xxx",
  };
  rawmap_t rm = make_rawmap(5, 3, 1, 1, lines);
  game_t g = make_game(&rm);

  /* cells beyond the raw line should be floor */
  assert(get_cell(&g, 1, 1) == FLOOR);
  assert(get_cell(&g, 2, 1) == FLOOR);
  assert(get_cell(&g, 3, 1) == FLOOR);
  assert(get_cell(&g, 4, 1) == FLOOR);

  free_game(&g);
  free_rawmap(&rm);
}

/* Run all unit tests. */
void run_tests(void) {
  test_basic_movement();
  test_wall_block();
  test_push_movable();
  test_push_one_move();
  test_push_into_hole();
  test_bix_falls_in_hole();
  test_win();
  test_push_blocked();
  test_push_two_blocks();
  test_reset_command();
  test_incomplete_map();
}

// --- MAIN ---
int main(int argc, char **argv) {
  run_tests();

  /* read map file or create default map */
  rawmap_t rawmap = argc < 2 ? make_default_rawmap() : read_map_file(argv[1]);

  game_t game = make_game(&rawmap); /* convert rawmap to initial game state */
  run_game(&game, &rawmap);

  /* FREEDOMMMMMM */
  free_game(&game);
  free_rawmap(&rawmap);
  return 0;
}
