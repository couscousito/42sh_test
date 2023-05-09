/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** my_strcpy
*/

#include "my.h"

char *my_strcpy(const char *source)
{
    int len_source = my_strlen(source);
    char *new = malloc(sizeof(char) * (len_source + 1));
    for (int i = 0; source[i]; i++)
        new[i] = source[i];
    new[len_source] = '\0';
    return new;
}
