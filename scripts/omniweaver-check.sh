#!/bin/sh
# Local check for OMNIWEAVER — mirrors .github/workflows/omniweaver.yml.
# Usage: sh scripts/omniweaver-check.sh
# Compiles omniweaver.cpp with the same flags as the workflow, then runs
# the same three smoke tests. Exits non-zero on the first failure.
# The program writes omniweaver_log.txt / omniweaver_memory.txt /
# omniweaver_archive.txt at runtime, so the smoke tests run in a temp
# directory to keep the repo clean.
set -eu

cd "$(dirname "$0")/.."

echo "Compiling omniweaver.cpp..."
g++ -std=c++17 -Wall -Wextra -o /tmp/omniweaver_check omniweaver.cpp
echo "Compile OK."

RUN_DIR=$(mktemp -d /tmp/omniweaver_check_run.XXXXXX)
trap 'rm -rf "$RUN_DIR" /tmp/omniweaver_check' EXIT
cd "$RUN_DIR"

echo "Smoke test 1: start up, status, and shut down..."
output=$(printf 'status\nquit\n' | /tmp/omniweaver_check)
echo "$output" | grep -q "OMNIWEAVER"
echo "$output" | grep -q "Version: 1.0.0"
echo "$output" | grep -q "Core: ONLINE"
echo "$output" | grep -q "Registered systems: 4"
echo "$output" | grep -q "OmniWeaver shutting down."
echo "Smoke test 1 OK."

echo "Smoke test 2: MathEngine (5 multiply 10)..."
output=$(printf 'calc multiply 5 10\nquit\n' | /tmp/omniweaver_check)
echo "$output" | grep -q "Calculation: 5 multiply 10 = 50"
echo "Smoke test 2 OK."

echo "Smoke test 3: MemoryEngine (remember and recall)..."
output=$(printf 'remember test note\nrecall\nquit\n' | /tmp/omniweaver_check)
echo "$output" | grep -q "MemoryEngine: Information stored successfully."
echo "$output" | grep -q "test note"
echo "Smoke test 3 OK."

echo "All OMNIWEAVER checks passed."
