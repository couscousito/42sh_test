/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** pipe_tools
*/

#include "project.h"

void get_num_pipes(sts *v, char *line)
{
    int count = 0;
    for (int i = 0; line[i]; i++)
        if (line[i] == '|')
            count++;
    v->numPipes = count;
}

void create_pipes(sts *v)
{
    int *pipefds = malloc(sizeof(int) * (2 * v->numPipes));
    for (int i = 0; i < (v->numPipes); i++){
        if (pipe(pipefds + i * 2) < 0) {
            perror("couldn't pipe");
            return;
        }
    }
    v->pipefds = pipefds;
}
