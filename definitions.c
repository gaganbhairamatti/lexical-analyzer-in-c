#include <string.h>
#include "header.h"

/*Compares the given word with all keywords.Returns 1 if it is a keyword, otherwise returns 0.*/
int check_keyword(const char *word)
{
    const char *keywords[] = {
        "auto","break","case","char","const","continue","default","do",
        "double","else","enum","extern","float","for","goto","if",
        "int","long","register","return","short","signed","sizeof","static",
        "struct","switch","typedef","union","unsigned","void","volatile","while"
    };

    for (int i = 0; i < 32; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

/*Checks whether the given character is a valid operator or not*/
int check_operator(char ch)
{
    char op_list[] = "+-*/%=<>!";

    for (int i = 0; op_list[i] != '\0'; i++)
    {
        if (ch == op_list[i])
            return 1;
    }
    return 0;
}

/* Checks for special symbols such as brackets, commas, semicolons etc.*/
int check_symbol(char ch)
{
    char sym_list[] = "(){}[],;:";

    for (int i = 0; sym_list[i] != '\0'; i++)
    {
        if (ch == sym_list[i])
            return 1;
    }
    return 0;
}