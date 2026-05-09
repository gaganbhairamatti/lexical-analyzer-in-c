#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"


/* Keyword checker */
int check_keyword(const char *word);

/* Operator checker */
int check_operator(char ch);

/* Symbol checker */
int check_symbol(char ch);

#endif