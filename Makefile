# Simplified Makefile for C Programming Course Exercises
# Usage: make N (where N is the series number) or make all

# Compiler and flags
CC = gcc
CFLAGS = -w -std=c99

# Find all series directories
SERIES_NUMBERS := $(shell find week -maxdepth 1 -type d -name "[0-9]*" | sed 's|week/||' | sort -n)

# Default target - show help
help:
	@echo "C Programming Course Build System"
	@echo "================================="
	@echo "Usage: make N (where N is the series number)"
	@echo "       make all (compile all series)"
	@echo "Available series: $(SERIES_NUMBERS)"

# Target to compile all series
all:
	@echo "Compiling all series..."; \
	FAILED=0; \
	for SERIES in $(SERIES_NUMBERS); do \
		echo "Compiling series $$SERIES..."; \
		FILES=$$(find week/$$SERIES -name "*.c" -type f -not -empty -exec grep -l "int main" {} \; 2>/dev/null); \
		if [ -n "$$FILES" ]; then \
			for FILE in $$FILES; do \
				BINARY=$$(echo $$FILE | sed 's/\.c$$//'); \
				if grep -q "#include <math.h>" "$$FILE" 2>/dev/null; then \
					if $(CC) $(CFLAGS) "$$FILE" -lm -o "$$BINARY" >/dev/null 2>&1; then \
						echo "[PASS] $$BINARY"; \
					else \
						echo "[FAIL] $$BINARY"; \
						FAILED=1; \
					fi; \
				else \
					if $(CC) $(CFLAGS) "$$FILE" -o "$$BINARY" >/dev/null 2>&1; then \
						echo "[PASS] $$BINARY"; \
					else \
						echo "[FAIL] $$BINARY"; \
						FAILED=1; \
					fi; \
				fi; \
			done; \
		else \
			echo "No executable files found in series $$SERIES"; \
		fi; \
	done; \
	if [ $$FAILED -eq 0 ]; then \
		echo "All series compiled successfully!"; \
	else \
		echo "Some compilations failed."; \
		exit 1; \
	fi

# Create targets for each series number
$(SERIES_NUMBERS):
	@SERIES_DIR=week/$@; \
	if [ ! -d "$$SERIES_DIR" ]; then \
		echo "Series $@ not found!"; \
		exit 1; \
	fi; \
	echo "Compiling series $@..."; \
	FILES=$$(find $$SERIES_DIR -name "*.c" -type f -not -empty -exec grep -l "int main" {} \; 2>/dev/null); \
	if [ -z "$$FILES" ]; then \
		echo "No executable files found in series $@"; \
		exit 0; \
	fi; \
	FAILED=0; \
	for FILE in $$FILES; do \
		BINARY=$$(echo $$FILE | sed 's/\.c$$//'); \
		if grep -q "#include <math.h>" "$$FILE" 2>/dev/null; then \
			if $(CC) $(CFLAGS) "$$FILE" -lm -o "$$BINARY" >/dev/null 2>&1; then \
				echo "[PASS] $$BINARY"; \
			else \
				echo "[FAIL] $$BINARY"; \
				FAILED=1; \
			fi; \
		else \
			if $(CC) $(CFLAGS) "$$FILE" -o "$$BINARY" >/dev/null 2>&1; then \
				echo "[PASS] $$BINARY"; \
			else \
				echo "[FAIL] $$BINARY"; \
				FAILED=1; \
			fi; \
		fi; \
	done; \
	exit $$FAILED

.PHONY: help all $(SERIES_NUMBERS)
