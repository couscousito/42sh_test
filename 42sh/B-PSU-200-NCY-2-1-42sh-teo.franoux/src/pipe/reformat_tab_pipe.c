/*
** EPITECH PROJECT, 2023
** bs-minishell2
** File description:
** reformat_tab_pipe
*/

#include "project.h"

void reformat_start(char **tab, int index)
{
    int len = my_strlen(tab[index]) - 1;
    char *new = malloc(sizeof(char) * (len + 1));
    for (int i = 1; tab[index][i]; i++)
        new[i - 1] = tab[index][i];
    new[len] = '\0';
    free(tab[index]);
    tab[index] = new;
}

void reformat_end(char **tab, int index)
{
    int len = my_strlen(tab[index]) - 1;
    char *new = malloc(sizeof(char) * (len + 1));
    for (int i = 0; tab[index][i + 1]; i++)
        new[i] = tab[index][i];
    new[len] = '\0';
    free(tab[index]);
    tab[index] = new;
}

void reformat_tab(char **tab)
{
    for (int i = 0; tab[i]; i++) {
        if (tab[i][0] == ' ')
            reformat_start(tab, i);
        if (tab[i][my_strlen(tab[i])] == ' ')
            reformat_end(tab, i);
    }
}
