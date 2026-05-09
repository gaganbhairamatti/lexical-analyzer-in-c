/***************************************************************************************************
 * Project Name : Lexical Analyzer
 * Name         : Gagan Bhairamatti
 *
 * Description  :This program implements a basic Lexical Analyzer for the C programming language.
    It scans a given C source file character by character and identifies different
    types of tokens such as:
     - Keywords
     - Identifiers
     - Numbers
     - String Literals
     - Operators
     - Special Symbols
    Also it can check for basic error like brackets and semicolon missing.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

int main(int argc, char *argv[])
{
    /* Validate command line input */
    if (argc != 2)
    {
        printf("Usage: %s <source_file.c>\n", argv[0]);
        return 1;
    }

    //Open the source file
    FILE *src = fopen(argv[1], "r");
    if (!src)
    {
        printf("Error: Unable to open source file\n");
        return 1;
    }

    /* Check if main() exists in file */
    int main_found = 0;
    char line_buf[1024];

    while (fgets(line_buf, sizeof(line_buf), src))
    {
        if (strstr(line_buf, "main("))
        {
            main_found = 1;
            break;
        }
    }

    if (!main_found)
        printf("Warning: main() function not found\n");

    rewind(src);  // go back to start of file


/* Check for missing semicolon */
    int line_check = 1;
    rewind(src); // Ensure we start from the beginning
    while (fgets(line_buf, sizeof(line_buf), src))
    {
        // 1. Remove newline and trailing spaces
        int len = strlen(line_buf);
        while(len > 0 && isspace(line_buf[len-1])) {
            line_buf[--len] = '\0';
        }

        // 2. Skip empty lines, preprocessor, and lines with braces/parentheses
        if (len == 0 || line_buf[0] == '#' || 
            strchr(line_buf, '{') || strchr(line_buf, '}') || 
            strchr(line_buf, '(')) 
        {
            line_check++;
            continue;
        }

        // 3. If it's a regular statement and has no semicolon, flag it
        if (strchr(line_buf, ';') == NULL)
        {
            printf(RED"Error (Line %d): Missing semicolon\n" RESET, line_check);
        }

        line_check++;
    }

    rewind(src);
    printf(YELLOW"\n--- Lexical Analysis Started ---\n\n"RESET);

    char token[300];
    char ch;
    int line_no = 1;

    /* Counters to track brackets */
    int curly = 0, round = 0, square = 0;

    //now read file character by character
    while ((ch = fgetc(src)) != EOF)
    {
        // Track new lines
        if (ch == '\n')
        {
            line_no++;
            continue;
        }

        /* Ignore spaces or tabs */
        if (isspace(ch))
            continue;

        /* Ignore preprocessor directives */
        if (ch == '#')
        {
            while ((ch = fgetc(src)) != EOF && ch != '\n');
            line_no++;
            continue;
        }

        /* Identifiers or keywords */
        if (isalpha(ch) || ch == '_')  //starts with alphabet or underscore
        {
            int i = 0;
            token[i++] = ch;   // store first character

            while ((ch = fgetc(src)) != EOF && (isalnum(ch) || ch == '_'))
                token[i++] = ch;

            token[i] = '\0';
            if (ch != EOF)   //we read one extra character , put it back
                ungetc(ch, src);

            printf("%-15s : %s\n",
                   check_keyword(token) ? "Keyword" : "Identifier",token);
            continue;
        }

        /* Numbers */
        if (isdigit(ch))
        {
            int i = 0, dot_seen = 0;
            token[i++] = ch;

            while ((ch = fgetc(src)) != EOF &&
                   (isdigit(ch) || ch == '.'))
            {
                if (ch == '.')
                {
                    if (dot_seen)
                        break;
                    dot_seen = 1;
                }
                token[i++] = ch;
            }

            token[i] = '\0';
            if (ch != EOF)
                ungetc(ch, src);

            printf("%-15s : %s\n", "Constant", token);
            continue;
        }

        /* for String literals */
        if (ch == '"')
        {
            int i = 0;
            token[i++] = ch;

            while ((ch = fgetc(src)) != EOF)
            {
                token[i++] = ch;
                if (ch == '"')
                    break;
                if (ch == '\n')
                    line_no++;
            }

            token[i] = '\0';
            printf("String Literal  : %s\n", token);
            continue;
        }

        /* Single-line and multi-line comments */
        if (ch == '/')     //single line
        {
            char next = fgetc(src);
            if (next == '/')
            {
                while ((ch = fgetc(src)) != EOF && ch != '\n');
                line_no++;
                continue;
            }
            else if (next == '*')  //multi-line
            {
                char prev = 0;
                while ((ch = fgetc(src)) != EOF)
                {
                    if (ch == '\n')
                        line_no++;
                    if (prev == '*' && ch == '/')
                        break;
                    prev = ch;
                }
                continue;
            }
            else
            {
                ungetc(next, src);
                printf("Operator        : /\n");
                continue;
            }
        }

        /* Brackets handling */
        if (ch == '{') curly++;
        if (ch == '}') curly--;
        if (ch == '(') round++;
        if (ch == ')') round--;
        if (ch == '[') square++;
        if (ch == ']') square--;

        if (check_symbol(ch)) //check if it's a symbol
        {
            printf("Symbol          : %c\n", ch);
            continue;
        }

        if (check_operator(ch)) //check for operator
        {
            printf("Operator        : %c\n", ch);
            continue;
        }

        /* Anything unknown */
        printf("Error (Line %d) : Invalid token '%c'\n", line_no, ch);
    }

    /* Final bracket validation */
    if (curly > 0)
        printf(RED"Error: Missing %d closing '}'\n" RESET, curly);
    if (round > 0)
        printf(RED"Error: Missing %d closing ')'\n" RESET, round);
    if (square > 0)
        printf(RED"Error: Missing %d closing ']'\n" RESET, square);

    fclose(src);
    printf(YELLOW"\n--- Lexical Analysis Completed ---\n"RESET);
    return 0;
}
