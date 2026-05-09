# Lexical Analyzer in C

A simple and modular **Lexical Analyzer** developed using the **C programming language** as part of Compiler Design concepts.

This project scans source code and identifies different tokens such as:

- Keywords
- Identifiers
- Operators
- Constants
- Special Symbols

The project demonstrates the **Lexical Analysis phase** of a compiler.

---

# Features

- Detects C language keywords
- Identifies identifiers and variables
- Recognizes operators and symbols
- Classifies constants and numbers
- Modular implementation using multiple source files
- Beginner-friendly compiler design project

---

# Technologies Used

- C Programming Language
- GCC Compiler
- Compiler Design Concepts

---

# Project Structure

```bash
lexical-analyzer-in-c/
│
├── README.md
├── main.c
├── definitions.c
├── header.h
└── sample.c
```

---

# File Description

- `main.c` → Main driver program
- `definitions.c` → Contains token identification functions and logic
- `header.h` → Header file containing function declarations
- `sample.c` → Sample input source code for lexical analysis

---

# How It Works

The lexical analyzer reads the input source code character by character and groups them into meaningful tokens.

Example token categories:

| Input | Token Type |
|------|------|
| int | Keyword |
| a | Identifier |
| = | Operator |
| 10 | Constant |
| ; | Special Symbol |

---

# Sample Input

```c
int a = 10;
float b = 20.5;
```

---

# Sample Output

```txt
Keyword : int
Identifier : a
Operator : =
Constant : 10
Special Symbol : ;

Keyword : float
Identifier : b
Operator : =
Constant : 20.5
Special Symbol : ;
```

---

# How to Compile and Run

## Compile

```bash
gcc main.c definitions.c -o lexer
```

## Run

```bash
./lexer
```

---

# Learning Outcomes

This project helped in understanding:

- Compiler Design Basics
- Lexical Analysis Process
- Token Classification
- Modular Programming in C
- Header File Usage
- Source Code Processing

---

# Future Improvements

- Add comment detection
- Support multi-line input
- Improve token classification
- Add syntax analyzer integration
- Build mini compiler front-end

---

# Author

## Gagan Bhairamatti

Engineering Graduate | Embedded Systems & Software Enthusiast
