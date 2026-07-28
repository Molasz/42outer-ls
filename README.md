# ft_ls

_This project has been created as part of the 42 curriculum by molasz-a._

> Part of [42 Barcelona — molasz-a](https://github.com/Molasz/42), a monorepo centralizing every project completed at 42 Barcelona.

## Description

**ft_ls** is a reimplementation of the Unix `ls` command in C. The project covers directory traversal, file metadata access, and command-line option parsing.

It is built on top of a custom `ft_printf` library that is included as a submodule dependency in `printf/`.

---

## Supported Flags

The following flags are implemented:

| Flag | Description                                      |
| ---- | ------------------------------------------------ |
| `-l` | Long listing format (detailed information)       |
| `-R` | Recursive listing (list subdirectories)          |
| `-a` | Include hidden files (files starting with `.`)   |
| `-r` | Reverse order                                    |
| `-t` | Sort by modification time                        |

---

## Features

- Lists files and directories with the same basic behavior as the Unix `ls` command.
- Supports recursive traversal when `-R` is passed.
- Applies sorting by name, time, and reverse order.
- Includes hidden entries when `-a` is specified.
- Displays detailed file information in long format with `-l`.

---

## Usage

```bash
# Compile the program
make

# List current directory contents
./ft_ls

# List current directory with long format
./ft_ls -l

# List all files including hidden ones, sorted by time
./ft_ls -a -t

# Recursively list directory contents
./ft_ls -R
```

---

## Build / Cleanup

```bash
make         # compile ft_ls and its ft_printf dependency
make clean   # remove object files
make fclean  # remove object files and executable
make re      # rebuild from scratch
```

---

## Project Layout

- `src/`       : source files for `ft_ls`
- `includes/`  : project headers
- `printf/`    : dependency containing `ft_printf`
- `ft_ls`      : compiled executable

---

_molasz-a · 42 Barcelona_