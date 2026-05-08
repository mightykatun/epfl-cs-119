#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

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

int main(int argc, char **argv) {
  // Choisir la carte par défaut, ou celle donnée en argument du programme
  rawmap_t rawmap = argc < 2 ? make_default_rawmap() : read_map_file(argv[1]);

  // Ici, votre programme

  // Ne pas oublier de libérer la carte brute.
  free_rawmap(&rawmap);

  return 0;
}
