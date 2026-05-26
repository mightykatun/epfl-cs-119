# ICC Mécanique BA2

Dépot de travail pour un cours de programmation en C.

## Contenu

- `week/<semaine #>` : exercices et notes organises par semaine
- `week/projet/` : projet de midterm "bix" `puzzle.c`
- `week/*/README.md` : resumé rapide des sujets vus chaque semaine
- `Makefile` : compilation des exercices par semaine ou en une fois

## Prérequis

- `gcc`
- `make`
- `bash`

## Compilation

Depuis la racine du depot :

```bash
make help
make all
make 3
make projet
```

- `make all` compile tous les fichiers C executables trouvés dans `week/`
- `make <numero/"projet">` compile une semaine precise

## Projet

Le projet de midterm se trouve dans `week/projet/`.

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
