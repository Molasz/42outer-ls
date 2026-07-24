#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
CYAN='\033[0;36m'
YELLOW='\033[0;33m'
NC='\033[0m'

if [ ! -f "./ft_ls" ]; then
    echo -e "${RED}Error: ./ft_ls not found. Compile it before running the tests.${NC}"
    exit 1
fi

run_test() {
    TEST_NAME="$1"
    FLAGS="$2"
    TARGET="$3"

    printf "%-25s (%-8s %-10s)... " "[$TEST_NAME]" "$FLAGS" "$TARGET"

    LC_ALL=C /bin/ls --color=never $FLAGS $TARGET 2>/dev/null | xargs -n 1 > /tmp/sys_ls_out
    LC_ALL=C ./ft_ls $FLAGS $TARGET 2>/dev/null | xargs -n 1 > /tmp/ft_ls_out

    if diff -q /tmp/sys_ls_out /tmp/ft_ls_out > /dev/null; then
        echo -e "${GREEN}✔ OK${NC}"
    else
        echo -e "${RED}✘ KO${NC}"
        echo -e "${CYAN}┌── MISMATCH FOUND (Git Diff Style) ─────────────────────────────┐${NC}"
        echo -e "${RED}│ --- [ EXPECTED: /bin/ls ] ${NC}"
        echo -e "${GREEN}│ +++ [ RECEIVED: ./ft_ls ] ${NC}"
        echo -e "${CYAN}└────────────────────────────────────────────────────────────────┘${NC}"
        
        diff -u -U 3 --color=always /tmp/sys_ls_out /tmp/ft_ls_out | tail -n +3 | head -n 25
        echo -e "${YELLOW}------------------------------------------------------------------${NC}"
    fi
}

echo -e "${CYAN}=== STARTING FT_LS BLIND FORMAT TESTS ===${NC}"

# Basic tests
run_test "Current Directory" "" "."
run_test "Specific Directory" "" "src"
run_test "Multiple Arguments" "" "Makefile README.md src includes"

# Flag tests
run_test "Recursive Flag" "-R" "."
run_test "All files Flag" "-a" "."
run_test "Reverse Flag" "-r" "."
run_test "Time sort Flag" "-t" "."
run_test "Long listing Flag" "-l" "src"

# Combined flag tests
run_test "Recursive + All" "-Ra" "."
run_test "Reverse + Time" "-rt" "."
run_test "All + Long + Reverse" "-lra" "src"
run_test "The Ultimate Combo" "-lRart" "."

# Cleanup
rm -f /tmp/sys_ls_out /tmp/ft_ls_out
echo -e "${CYAN}=== TESTS COMPLETED ===${NC}"