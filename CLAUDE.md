# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

This is a C programming course repository organized into 5 weekly series (`series/1/` through `series/5/`). The course is taught in French. Each series contains lecture examples (`lecture-0N.c`), numbered exercises (`ex1.c`, `ex2.c`, etc.), compiled binaries, PDFs, and a README describing the week's theme.

## Building and Running

There is no build system. Compile individual files with `gcc`:

```sh
gcc series/N/exM.c -o series/N/exM          # basic compilation
gcc series/N/exM.c -o series/N/exM -lm      # when using <math.h>
```

Run a compiled exercise:
```sh
./series/N/exM
```

## Series Themes

| Series | Topic |
|--------|-------|
| 1 | Variables, constants, `printf`, environment setup |
| 2 | `scanf`, booleans (`<stdbool.h>`), conditionals, intro to functions |
| 3 | Functions and loops |
| 4 | Arrays |
| 5 | Strings and array review |

## Code Patterns

- **Size of array**: `int length = sizeof(arr) / sizeof(*arr);`
- **String iteration**: null-terminator loop `while (character != '\0')`
- **Math functions**: include `<math.h>` and link with `-lm`
- Exercises may have multiple implementations of the same function (e.g., `len_str_1`, `len_str_2`) to demonstrate different approaches
