/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** redirect_tools
*/

#include "project.h"

void stdint_simple(sts *v, char *cmd, int index)
{
    int no_empty_name = 0;
    for (int j = index + 1; cmd[j]; j++)
        if (cmd[j] != ' ') no_empty_name = 1;
    if (no_empty_name) {
        v->rev_redirect = copy_str_n(cmd, index);
    }
    cmd[index] = '\0';
}

void stdin_double_redirect(sts *v, char *cmd, int index)
{
    int no_empty_name = 0;
    for (int j = index + 1; cmd[j]; j++)
        if (cmd[j] != ' ') no_empty_name = 1;
    if (no_empty_name )
        v->dbl_rev_redirect = copy_str_n(cmd, index);
    cmd[index - 1] = '\0';
}

void affect_simple_redirection(sts *v, char *cmd, int index)
{
    if (v->redirect_dbl != NULL) return;
    int no_empty_name = 0;
    for (int j = index + 1; cmd[j]; j++)
        if (cmd[j] != ' ') no_empty_name = 1;
    if (no_empty_name)
        v->redirect = copy_str_n(cmd, index);
    cmd[index] = '\0';
}

void double_redirect_stdout(sts *v, char *cmd, int index)
{
    if (v->redirect != NULL) return;
    int no_empty_name = 0;
    for (int j = index + 1; cmd[j]; j++)
        if (cmd[j] != ' ') no_empty_name = 1;
    if (no_empty_name)
        v->redirect_dbl = copy_str_n(cmd, index);
    cmd[index - 1] = '\0';
}

int check_redirection(sts *v, char *cmd)
{
    for (int i = 0; cmd[i]; i++) {
        if (cmd[i] == '>' && cmd[i + 1] != '>' && cmd[i - 1] != '>')
            affect_simple_redirection(v, cmd, i);
        if (cmd[i] == '>' && cmd[i + 1] == '>')
            double_redirect_stdout(v, cmd, i + 1);
        if (cmd[i] == '<' && cmd[i + 1] != '<' && cmd[i - 1] != '<')
            stdint_simple(v, cmd, i);
        if (cmd[i] == '<' && cmd[i + 1] == '<')
            stdin_double_redirect(v, cmd, i + 1);
    }
    return (0);
}
