/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** my_strcmp
*/

#include "my.h"

int my_strcmp(char *f, char *s)
{
    int first_l = my_strlen(f);
    int second_l = my_strlen(s);
    if (first_l < second_l)
        return -1;
    if (first_l > second_l)
        return 1;
    for (int i = 0; f[i]; i++) {
        if (f[i] < s[i])
            return -1;
        if (f[i] > s[i])
            return 1;
    }
    return 0;
}
