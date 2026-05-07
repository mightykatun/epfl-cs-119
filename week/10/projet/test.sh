#!/bin/bash

PASS=0
FAIL=0

# --- COMPILE ---
echo "=== Compilation ==="
gcc -Wall -Wextra -fsanitize=address,undefined -g -o puzzle puzzle.c 2>compile_errors.txt
if [ $? -ne 0 ]; then
    echo "FAIL: compilation failed"
    cat compile_errors.txt
    rm -f compile_errors.txt
    exit 1
fi
if [ -s compile_errors.txt ]; then
    echo "WARN: compiled with warnings:"
    cat compile_errors.txt
else
    echo "OK: compiled cleanly"
fi
rm -f compile_errors.txt
echo ""

# --- RUN ONE TEST ---
# Usage: run_test <label> <map_file> <input_file> <expected_output_file>
run_test() {
    label="$1"
    map="$2"
    input="$3"
    expected="$4"
    actual=$(mktemp)

    ./puzzle "$map" < "$input" > "$actual" 2>&1
    if diff -q "$expected" "$actual" > /dev/null 2>&1; then
        echo "OK:   $label"
        PASS=$((PASS + 1))
    else
        echo "FAIL: $label"
        diff -u "$expected" "$actual"
        FAIL=$((FAIL + 1))
    fi
    rm -f "$actual"
}

# --- TESTS ---
echo "=== Tests ==="
run_test "level1"        map/level1.txt        map/level1-test-input.txt        map/level1-test-output.txt
run_test "level2"        map/level2.txt        map/level2-test-input.txt        map/level2-test-output.txt
run_test "incomplete-map" map/incomplete-map.txt map/incomplete-map-test-input.txt map/incomplete-map-test-output.txt
echo ""

# --- SUMMARY ---
echo "=== Summary ==="
echo "$PASS passed, $FAIL failed"
[ $FAIL -eq 0 ] && exit 0 || exit 1
