# ICC

Depot de travail pour un cours de programmation en C.

## Contenu

- `week/1` a `week/10` : exercices et notes organises par semaine
- `week/projet/` : projet principal autour de `puzzle.c`
- `week/*/README.md` : resume rapide des sujets vus chaque semaine
- `Makefile` : compilation des exercices par semaine ou en une fois

## Prerequis

- `gcc`
- `make`
- `bash`

## Compilation

Depuis la racine du depot :

```bash
make help
make all
make 1
make 10
```

- `make all` compile les fichiers C executables trouves dans `week/`
- `make <numero>` compile une semaine precise

## Projet puzzle

Le projet principal se trouve dans `week/projet/`.

Compilation manuelle :

```bash
gcc -Wall -Wextra -fsanitize=address,undefined -g -o puzzle puzzle.c
```

Tests fournis :

```bash
cd week/projet
bash test.sh
```

Execution manuelle d'un niveau :

```bash
./puzzle map/level1.txt < map/level1-test-input.txt
```

## Structure

```text
.
|- Makefile
|- week/
|  |- 1/ ... 10/
|  |- projet/
|  |  |- puzzle.c
|  |  |- test.sh
|  |  `- map/
|  `- DONE.md
```

## Notes

- Les fichiers PDF dans les dossiers `week/` contiennent les enonces et solutions du cours.
- Les tests du projet comparent la sortie exacte du programme avec les fichiers attendus.
