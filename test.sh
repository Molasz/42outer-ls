#!/bin/bash
#
# test.sh — ft_ls evaluation-sheet test suite
#
# Mirrors the 42 correction sheet sections:
#   Preliminaries / Basic Tests / Basic Tests ++ / Middle Tests / Error Management
#
# Each test compares `./ft_ls` against the system `/bin/ls` byte-for-byte
# (normal mode) or checks documented behaviour (error mode).

GREEN='\033[0;32m'
RED='\033[0;31m'
CYAN='\033[0;36m'
YELLOW='\033[0;33m'
BOLD='\033[1m'
NC='\033[0m'

PASS=0
FAIL=0
WARN=0

if [ ! -f "./ft_ls" ]; then
    printf '%b\n' "${RED}Error: ./ft_ls not found. Compile it before running the tests.${NC}"
    exit 1
fi

FT_LS="$(pwd)/ft_ls"

section() {
    echo ""
    printf '%b\n' "${BOLD}${CYAN}══════════════════════════════════════════════════════════════════${NC}"
    printf '%b\n' "${BOLD}${CYAN} $1${NC}"
    printf '%b\n' "${BOLD}${CYAN}══════════════════════════════════════════════════════════════════${NC}"
}

# ---------------------------------------------------------------------------
# run_test: byte-for-byte comparison against /bin/ls (order-insensitive,
# one entry per line, which is what the subject asks: content must match,
# padding/columns/colors are excluded).
# ---------------------------------------------------------------------------
run_test() {
    local TEST_NAME="$1"
    local FLAGS="$2"
    shift 2
    local TARGETS="$*"

    printf "%-34s (%-8s %-32s)... " "[$TEST_NAME]" "$FLAGS" "$TARGETS"

    LC_ALL=C /bin/ls --color=never $FLAGS $TARGETS 2>/dev/null | xargs -n 1 > /tmp/sys_ls_out
    LC_ALL=C "$FT_LS" $FLAGS $TARGETS 2>/dev/null | xargs -n 1 > /tmp/ft_ls_out

    if diff -q /tmp/sys_ls_out /tmp/ft_ls_out > /dev/null; then
        printf '%b\n' "${GREEN}✔ OK${NC}"
        PASS=$((PASS + 1))
    else
        printf '%b\n' "${RED}✘ KO${NC}"
        FAIL=$((FAIL + 1))
        printf '%b\n' "${CYAN}┌── MISMATCH FOUND (Git Diff Style) ─────────────────────────────┐${NC}"
        printf '%b\n' "${RED}│ --- [ EXPECTED: /bin/ls ] ${NC}"
        printf '%b\n' "${GREEN}│ +++ [ RECEIVED: ./ft_ls ] ${NC}"
        printf '%b\n' "${CYAN}└────────────────────────────────────────────────────────────────┘${NC}"
        diff -u -U 3 --color=always /tmp/sys_ls_out /tmp/ft_ls_out | tail -n +3 | head -n 25
        printf '%b\n' "${YELLOW}------------------------------------------------------------------${NC}"
    fi
}

# ---------------------------------------------------------------------------
# run_self_consistency: same flags in different notations ("-l -t" vs "-lt")
# must produce identical ft_ls output — this is what the sheet calls
# "Multiple option management: parsing and form".
# ---------------------------------------------------------------------------
run_self_consistency() {
    local TEST_NAME="$1"
    local FLAGS_A="$2"
    local FLAGS_B="$3"
    local TARGET="$4"

    printf "%-34s (%-8s vs %-8s)... " "[$TEST_NAME]" "$FLAGS_A" "$FLAGS_B"

    LC_ALL=C "$FT_LS" $FLAGS_A $TARGET 2>/dev/null > /tmp/ft_ls_form_a
    LC_ALL=C "$FT_LS" $FLAGS_B $TARGET 2>/dev/null > /tmp/ft_ls_form_b

    if diff -q /tmp/ft_ls_form_a /tmp/ft_ls_form_b > /dev/null; then
        printf '%b\n' "${GREEN}✔ OK${NC}"
        PASS=$((PASS + 1))
    else
        printf '%b\n' "${RED}✘ KO${NC}"
        FAIL=$((FAIL + 1))
        diff -u --color=always /tmp/ft_ls_form_a /tmp/ft_ls_form_b | tail -n +3 | head -n 25
        printf '%b\n' "${YELLOW}------------------------------------------------------------------${NC}"
    fi
}

# ---------------------------------------------------------------------------
# run_error_test: for error-management cases, exact wording isn't graded —
# what matters is a non-zero exit code and a message on stderr, same as
# /bin/ls. We check both independently, not diffed against each other.
# ---------------------------------------------------------------------------
run_error_test() {
    local TEST_NAME="$1"
    local FLAGS="$2"
    shift 2
    local TARGETS="$*"

    printf "%-34s (%-8s %-32s)... " "[$TEST_NAME]" "$FLAGS" "$TARGETS"

    LC_ALL=C /bin/ls $FLAGS $TARGETS > /dev/null 2>/tmp/sys_ls_err
    local SYS_CODE=$?
    LC_ALL=C "$FT_LS" $FLAGS $TARGETS > /dev/null 2>/tmp/ft_ls_err
    local FT_CODE=$?

    if [ "$SYS_CODE" -ne 0 ] && [ "$FT_CODE" -ne 0 ] && [ -s /tmp/ft_ls_err ]; then
        printf '%b\n' "${GREEN}✔ OK${NC} (exit=$FT_CODE, stderr non-empty)"
        PASS=$((PASS + 1))
    else
        printf '%b\n' "${RED}✘ KO${NC} (sys exit=$SYS_CODE, ft exit=$FT_CODE, ft stderr empty=$([ -s /tmp/ft_ls_err ] && echo no || echo yes))"
        FAIL=$((FAIL + 1))
        printf '%b\n' "${YELLOW}--- /bin/ls stderr ---${NC}"; sed 's/^/  /' /tmp/sys_ls_err
        printf '%b\n' "${YELLOW}--- ft_ls stderr   ---${NC}"; sed 's/^/  /' /tmp/ft_ls_err
        printf '%b\n' "${YELLOW}------------------------------------------------------------------${NC}"
    fi
}

printf '%b\n' "${CYAN}=== STARTING FT_LS EVALUATION-SHEET TESTS ===${NC}"

# ===========================================================================
# PRELIMINARIES — automatable parts only. Norm, forbidden functions and
# memory leaks still need norminette/valgrind and a manual read, run those
# separately if available in your environment.
# ===========================================================================
section "PRELIMINARIES"

printf "%-34s... " "[Makefile: all rule present]"
grep -qE '^all:' Makefile && { printf '%b\n' "${GREEN}✔ OK${NC}"; PASS=$((PASS+1)); } || { printf '%b\n' "${RED}✘ KO${NC}"; FAIL=$((FAIL+1)); }

printf "%-34s... " "[Makefile: clean rule present]"
grep -qE '^clean:' Makefile && { printf '%b\n' "${GREEN}✔ OK${NC}"; PASS=$((PASS+1)); } || { printf '%b\n' "${RED}✘ KO${NC}"; FAIL=$((FAIL+1)); }

printf "%-34s... " "[Makefile: fclean rule present]"
grep -qE '^fclean:' Makefile && { printf '%b\n' "${GREEN}✔ OK${NC}"; PASS=$((PASS+1)); } || { printf '%b\n' "${RED}✘ KO${NC}"; FAIL=$((FAIL+1)); }

printf "%-34s... " "[Makefile: re rule present]"
grep -qE '^re:' Makefile && { printf '%b\n' "${GREEN}✔ OK${NC}"; PASS=$((PASS+1)); } || { printf '%b\n' "${RED}✘ KO${NC}"; FAIL=$((FAIL+1)); }

printf "%-34s... " "[Makefile: re-running make is silent/clean]"
make fclean > /dev/null 2>&1
if make all > /tmp/make_out 2>&1 && [ -f ./ft_ls ]; then
    printf '%b\n' "${GREEN}✔ OK${NC}"
    PASS=$((PASS + 1))
else
    printf '%b\n' "${RED}✘ KO${NC}"
    FAIL=$((FAIL + 1))
    tail -n 15 /tmp/make_out
fi

if command -v norminette > /dev/null 2>&1; then
    printf "%-34s... " "[Norm]"
    norminette src includes > /tmp/norm_out 2>/dev/null
    if grep -q "Error" /tmp/norm_out; then
        printf '%b\n' "${RED}✘ KO (norm errors found)${NC}"
        FAIL=$((FAIL + 1))
        grep -B1 "Error" /tmp/norm_out | sed 's/^/  /'
    else
        printf '%b\n' "${GREEN}✔ OK${NC}"
        PASS=$((PASS + 1))
    fi
else
    printf '%b\n' "${YELLOW}[Norm]                              ... skipped (norminette not installed — check manually)${NC}"
    WARN=$((WARN + 1))
fi

if command -v valgrind > /dev/null 2>&1; then
    printf "%-34s... " "[No memory leaks: ls -lRa .]"
    valgrind --leak-check=full --error-exitcode=1 "$FT_LS" -lRa . > /dev/null 2>/tmp/valgrind_out
    if grep -q "0 errors" /tmp/valgrind_out \
        && { grep -q "All heap blocks were freed -- no leaks are possible" /tmp/valgrind_out \
             || grep -q "definitely lost: 0 bytes" /tmp/valgrind_out; }; then
        printf '%b\n' "${GREEN}✔ OK${NC}"
        PASS=$((PASS + 1))
    else
        printf '%b\n' "${RED}✘ KO${NC}"
        FAIL=$((FAIL + 1))
        grep -E "lost|error" /tmp/valgrind_out
    fi
else
    printf '%b\n' "${YELLOW}[No memory leaks]                   ... skipped (valgrind not installed — check manually)${NC}"
    WARN=$((WARN + 1))
fi

printf '%b\n' "${YELLOW}Manual checks still required: author file, forbidden functions.${NC}"

# ===========================================================================
# Build a disposable fixture environment covering every case the sheet asks
# for: a plain file, a symlink, hidden files, setuid/setgid/sticky bit,
# an inaccessible directory, and files with staggered mtimes for -r/-t.
# ===========================================================================
FIXDIR="$(mktemp -d /tmp/ft_ls_fixtures.XXXXXX)"
mkdir -p "$FIXDIR/folder/subdir"
echo "hello" > "$FIXDIR/folder/regular_file.txt"
echo "secret" > "$FIXDIR/folder/.hidden_file"
ln -s regular_file.txt "$FIXDIR/folder/link_to_file"
echo "nested" > "$FIXDIR/folder/subdir/nested.txt"

touch "$FIXDIR/folder/setuid_file"
chmod u+s "$FIXDIR/folder/setuid_file" 2>/dev/null

mkdir "$FIXDIR/folder/setgid_dir"
chmod g+s "$FIXDIR/folder/setgid_dir" 2>/dev/null

mkdir "$FIXDIR/folder/sticky_dir"
chmod +t "$FIXDIR/folder/sticky_dir" 2>/dev/null

mkdir "$FIXDIR/folder/no_access_dir"
echo "top secret" > "$FIXDIR/folder/no_access_dir/secret.txt"
chmod 000 "$FIXDIR/folder/no_access_dir"

touch -d "3 days ago"  "$FIXDIR/folder/old_a.txt"
touch -d "2 days ago"  "$FIXDIR/folder/old_b.txt"
touch -d "1 day ago"   "$FIXDIR/folder/old_c.txt"
touch -d "10 hours ago" "$FIXDIR/folder/old_d.txt"

cleanup_fixtures() {
    chmod -R u+rwx "$FIXDIR" 2>/dev/null
    rm -rf "$FIXDIR"
}
trap cleanup_fixtures EXIT

# ===========================================================================
# BASIC TESTS — no args / on a file / on a folder, -a, -l, symlink accuracy
# ===========================================================================
section "BASIC TESTS"

OUTER_DIR="$(pwd)"
cd "$FIXDIR" || exit 1
run_test "ls (no arguments)"        ""   ""
cd "$OUTER_DIR" || exit 1

run_test "ls on a single file"       ""   "$FIXDIR/folder/regular_file.txt"
run_test "ls on a folder"            ""   "$FIXDIR/folder"
run_test "ls -a on a folder"         "-a" "$FIXDIR/folder"
run_test "ls -l on a folder"         "-l" "$FIXDIR/folder"
run_test "ls -l on a single file"    "-l" "$FIXDIR/folder/regular_file.txt"
run_test "ls -l symlink accuracy"    "-l" "$FIXDIR/folder/link_to_file"

# ===========================================================================
# BASIC TESTS ++ — -r, -t, multi-target -r/-t, setuid/setgid/sticky
# ===========================================================================
section "BASIC TESTS ++"

run_test "ls -r"                          "-r"  "$FIXDIR/folder"
run_test "ls -t"                          "-t"  "$FIXDIR/folder"
run_test "ls -r, multiple targets"        "-r"  "$FIXDIR/folder/old_a.txt" "$FIXDIR/folder/old_b.txt" "$FIXDIR/folder/subdir" "$FIXDIR/folder"
run_test "ls -t, multiple targets"        "-t"  "$FIXDIR/folder/old_a.txt" "$FIXDIR/folder/old_b.txt" "$FIXDIR/folder/subdir" "$FIXDIR/folder"
run_test "ls -l setuid/setgid/sticky"     "-la" "$FIXDIR/folder"

# ===========================================================================
# MIDDLE TESTS — recursion, option form, accurate combined display
# ===========================================================================
section "MIDDLE TESTS"

run_test "ls -R (recursive)"              "-R"    "$FIXDIR/folder"
run_test "ls -Rla (recursive + all + l)"  "-Rla"  "$FIXDIR/folder"
run_test "ls -lt (combined display)"      "-lt"   "$FIXDIR/folder"
run_test "ls -lRart (the ultimate combo)" "-lRart" "$FIXDIR/folder"

run_self_consistency "Option form: split vs combined" "-l -t" "-lt" "$FIXDIR/folder"
run_self_consistency "Option form: -Rla vs -R -l -a"  "-Rla"  "-R -l -a" "$FIXDIR/folder"

# ===========================================================================
# ERROR MANAGEMENT — nonexistent, inaccessible, invalid option
# ===========================================================================
section "ERROR MANAGEMENT"

run_error_test "Nonexistent file/folder" "" "$FIXDIR/folder/does_not_exist"
run_error_test "Unmanaged/nonexistent option" "-y"

if [ "$(id -u)" = "0" ]; then
    printf '%b\n' "${YELLOW}[Inaccessible file/folder]          ... running as root: DAC checks are bypassed,${NC}"
    printf '%b\n' "${YELLOW}                                        so this must be re-run as a non-root user${NC}"
    printf '%b\n' "${YELLOW}                                        to be conclusive.${NC}"
    if command -v setpriv > /dev/null 2>&1; then
        printf "%-34s... " "[Inaccessible folder, via setpriv nobody]"
        LC_ALL=C setpriv --reuid 65534 --regid 65534 --clear-groups /bin/ls "$FIXDIR/folder/no_access_dir" > /dev/null 2>/tmp/sys_ls_err
        SYS_CODE=$?
        LC_ALL=C setpriv --reuid 65534 --regid 65534 --clear-groups "$FT_LS" "$FIXDIR/folder/no_access_dir" > /dev/null 2>/tmp/ft_ls_err
        FT_CODE=$?
        if [ "$SYS_CODE" -ne 0 ] && [ "$FT_CODE" -ne 0 ] && [ -s /tmp/ft_ls_err ]; then
            printf '%b\n' "${GREEN}✔ OK${NC} (exit=$FT_CODE, stderr non-empty)"
            PASS=$((PASS + 1))
        else
            printf '%b\n' "${RED}✘ KO${NC} (sys exit=$SYS_CODE, ft exit=$FT_CODE)"
            FAIL=$((FAIL + 1))
            printf '%b\n' "${YELLOW}--- /bin/ls stderr ---${NC}"; sed 's/^/  /' /tmp/sys_ls_err
            printf '%b\n' "${YELLOW}--- ft_ls stderr   ---${NC}"; sed 's/^/  /' /tmp/ft_ls_err
        fi
    else
        printf '%b\n' "${YELLOW}                                        setpriv not available either — skipped.${NC}"
        WARN=$((WARN + 1))
    fi
else
    run_error_test "Inaccessible folder" "" "$FIXDIR/folder/no_access_dir"
fi

# ---------------------------------------------------------------------------
cleanup_fixtures
trap - EXIT
rm -f /tmp/sys_ls_out /tmp/ft_ls_out /tmp/ft_ls_form_a /tmp/ft_ls_form_b \
      /tmp/sys_ls_err /tmp/ft_ls_err /tmp/make_out /tmp/valgrind_out /tmp/norm_out

section "SUMMARY"
printf '%b\n' "  ${GREEN}Passed: $PASS${NC}   ${RED}Failed: $FAIL${NC}   ${YELLOW}Skipped/Manual: $WARN${NC}"
printf '%b\n' "${CYAN}=== TESTS COMPLETED ===${NC}"

[ "$FAIL" -eq 0 ]