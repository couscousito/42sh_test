/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** path_loop_find
*/

#include "project.h"

char *path_executable_with_name(char *path, char *name)
{
    int total = my_strlen(path) + my_strlen(name) + 1;
    int index = 0;
    char *new = malloc(sizeof(char) * (total + 1));
    new[total] = '\0';
    for (int i = 0; path[i]; i++, index++)
        new[index] = path[i];
    new[index++] = '/';
    for (int i = 0; name[i]; i++, index++)
        new[index] = name[i];
    return new;
}
