# ls

_This project has been created as part of the 42 curriculum by molasz-a._

> Part of [42 Barcelona — molasz-a](https://github.com/Molasz/42), a monorepo centralizing every project completed at 42 Barcelona.

## Description

**ls** is a project from the 42 curriculum that involves reimplementing the Unix `ls` command in C. This project provides a deeper understanding of file system operations, directory traversal, and command-line argument parsing.

The implementation supports several standard `ls` flags and options for listing directory contents.

---

## Supported Flags

The following flags are supported:

| Flag | Description                                      |
| ---- | ------------------------------------------------ |
| `-l` | Long listing format (detailed information)       |
| `-R` | Recursive listing (list subdirectories)          |
| `-a` | Include hidden files (files starting with .)     |
| `-r` | Reverse order                                    |
| `-t` | Sort by modification time                        |

---

## ⚙️ Instructions

```bash
# Compile the program
make

# Run the program (e.g., list current directory)
./ft_ls

# Run with flags (e.g., long listing)
./ft_ls -l

# Cleanup object files
make clean

# Cleanup object files and the executable
make fclean

# Recompile the program
make re
```

---

_molasz-a · 42 Barcelona_