# my_ls

A custom implementation of the Unix `ls` command, written in C++20.

I built this to get hands-on with lower-level systems programming - directory traversal, file metadata via `stat`, and replicating standard CLI tool behavior from scratch.

## Features

- `-a` - do not ignore entries starting with `.`
- `-h` - with `-l`, print sizes like `1K`, `234M`, `2G`
- `-i` - print the index number (inode) of each file
- `-l` - use a long listing format
- `-r` - reverse order while sorting
- `-s` - print the allocated size of each file, in blocks
- `-t` - sort by time, newest first
- `-F` - append an indicator (one of `*/=>@|`) to entries
- `--color[=WHEN]` - colorize output (`always`, `never`, or `auto`)

## Requirements
- CMake 3.20+
- A C++20 compiler
- POSIX-compliant system (uses `dirent.h`, `getopt.h`, etc.)

## Building

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## Usage

```bash
./my_ls [OPTION]... [FILE/DIR]
```

## Status

A work in progress built for learning purposes — not all flag combinations may be fully polished yet. Feedback and suggestions are welcome.
