# Inverted Search Engine in C

A menu-driven **Inverted Search Engine implemented in C** that indexes words from multiple text files and retrieves the files containing a queried word along with its occurrence count.

Instead of scanning every input file for every search, the program builds an inverted index that stores each word alongside the files in which it appears. This project demonstrates file handling, linked lists, dynamic memory management, searching, and database persistence in C.

## Features

- **Create Database** — Read text files and build an inverted index.
- **Display Database** — Display indexed words, filenames, and occurrence counts.
- **Update Database** — Add new text files to an existing index while rejecting duplicate files.
- **Search Words** — Find a word and display the files containing it with their occurrence counts.
- **Save Database** — Export the index to a text backup file.
- **Load Database** — Restore a saved index without reprocessing the original input files.
- **Input Validation** — Handle invalid menu choices and report file or database errors.

## How It Works

The program builds an inverted index that associates each unique word with the files containing it and the number of times it occurs in each file.

For example, suppose the input files contain:

`file1.txt`
```text
Hi hello how are you Hi Hello
```

`file2.txt`
```text
Hi Hello this is inverted search project
```

The resulting index includes entries such as:

| Word | Filename | Occurrences |
|---|---|---:|
| hello | data/file1.txt | 2 |
| hello | data/file2.txt | 1 |
| hi | data/file1.txt | 2 |
| hi | data/file2.txt | 1 |

When the user searches for `hi`, the program retrieves the matching file records and their occurrence counts from the index.

## Technologies and Concepts

- **Language:** C
- **Standard:** C11
- **Compiler:** GCC
- **Data Structures:** Singly linked lists
- **File Handling:** Reading text files and writing database backups
- **Memory Management:** Dynamic allocation and deallocation
- **Core Concepts:** String processing, searching, pointers, structures, and modular programming

## Project Structure

```text
Inverted_Search/
├── main.c
├── database.h
├── index.c
├── search.c
├── database_ops.c
├── data/
│   ├── file1.txt
│   ├── file2.txt
│   └── file3.txt
├── backup.txt
├── backup_updated.txt
├── README.md
└── .gitignore
```

- `main.c` — Menu-driven application and user interaction.
- `database.h` — Shared structures, constants, and function declarations.
- `index.c` — Database creation, word indexing, and index display.
- `search.c` — Word-search functionality.
- `database_ops.c` — Database updating, saving, and loading.
- `data/` — Sample text files used to build and test the index.
- `backup.txt` and `backup_updated.txt` — Sample saved database files.

## Prerequisites

Install GCC and ensure it is available in your terminal.

Verify the installation:

```bash
gcc --version
```

This project was developed and tested on Windows using GCC through MSYS2.

## Build Instructions

Open a terminal in the project directory and compile the source files:

```bash
gcc -std=c11 -Wall -Wextra main.c index.c search.c database_ops.c -o inverted_search.exe
```

Run the application in PowerShell:

```powershell
.\inverted_search.exe
```

## Usage

After launching the program, select an operation from the menu.

| Option | Operation |
|---:|---|
| 1 | Create Database |
| 2 | Display Database |
| 3 | Update Database |
| 4 | Search |
| 5 | Save Database |
| 6 | Load Database |
| 7 | Exit |

## Testing

The following functional scenarios were tested during development:

- Creating and displaying an index from multiple text files.
- Searching for existing and absent words.
- Verifying occurrence counts across different files.
- Adding a new file to an existing index.
- Rejecting an already-indexed file.
- Saving the index to a backup file.
- Restoring the index and verifying the saved occurrence counts.

The project was compiled with GCC using C11 and the warning flags `-Wall -Wextra`.

## Author

**Siddarth**

C Programming | Data Structures | File Handling | Systems Programming

---

*This project was developed as a C programming exercise to explore inverted indexing, linked lists, searching, and file-based database persistence.*