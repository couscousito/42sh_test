/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** redirect_tools
*/

#include "project.h"

char *copy_str_n(char *str, int start)
{
    int i = start + 1;
    int k = 0;
    int j = 0;
    for (k = i; str[k] == ' '; k++);
    k -= i;
    for (i += k; str[i] && str[i] != ' '; i++, j++);
    char *new = malloc(sizeof(char) * (j + 1));
    j = 0;
    for (i = start + 1 + k; str[i] && str[i] != ' '; i++, j++)
        new[j] = str[i];
    new[j] = '\0';
    return (new);
}
