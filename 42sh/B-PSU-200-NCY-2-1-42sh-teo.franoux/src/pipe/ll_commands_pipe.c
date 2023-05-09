/*
** EPITECH PROJECT, 2023
** bs-minishell2
** File description:
** ll_commands_pipe
*/

#include "project.h"

void free_dbl_tab(char **tab)
{
    for (int i = 0; tab[i]; i++)
        free(tab[i]);
    free(tab);
}

void free_ll_cmd_line(sts *v)
{
    cmdLine *tmp = NULL;
    cmdLine *head = v->cmds;
    while (head) {
        tmp = head;
        head = head->next;
        free_dbl_tab(tmp->argv);
    }
    v->cmds = NULL;
}

int add_ll_commands(sts *v, char *command)
{
    cmdLine *new = malloc(sizeof(cmdLine));
    cmdLine *tmp = v->cmds;
    char **cmd_comp = str_to_word_array(command, " \t");
    new->command = cmd_comp[0];
    new->argv = cmd_comp;
    new->next = NULL;
    if (v->cmds == NULL) {
        v->cmds = new;
        return (1);
    } else {
        for (; tmp->next; tmp = tmp->next);
        tmp->next = new;
    }
    return (0);
}

int create_command_pipe(sts *v, char **pipe)
{
    reformat_tab(pipe);
    for (int i = 0; pipe[i]; i++) {
        add_ll_commands(v, pipe[i]);
    }
    return (0);
}
