/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** my_strcat
*/

#include "my.h"

char *my_strcat(char *left, char *right)
{
    int total = my_strlen(left) + my_strlen(right);
    int index = 0;
    char *new = malloc(sizeof(char) * (total + 1));
    new[total] = '\0';
    for (int i = 0; left[i]; i++, index++) {
        new[index] = left[i];
    }
    for (int j = 0; right[j]; j++, index++) {
        new[index] = right[j];
    }
    new[index] = '\0';
    return new;
}
