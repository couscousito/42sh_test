/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** pipe_error_management
*/

#include "project.h"

static int check_end_str(char *cmd, int index)
{
    if (!cmd[index + 1] || cmd[index + 1] == ';') return (1);
    for (int i = index + 1; cmd[i] || cmd[i] == ';'; i++) {
        if (cmd[i] != ' ')
            return (0);
    }
    return (1);
}

static void check_pipe(sts *v, char *cmd, int *error)
{
    char *msg = "Invalid null command.\n";
    char *msg_redirect = "Missing name for redirect.\n";
    int err = 0;
    int redirect = 0;
    for (int i = 0; cmd[i] && !err && !redirect; i++) {
        if (cmd[i] == '|')
            err = check_end_str(cmd, i);
        if (cmd[i] == '>')
            redirect = check_end_str(cmd, i);
    }
    *error = err || redirect;
    if (err || redirect) v->exit_code = 1;
    if (err) v->name_error = my_strcpy(msg);
    if (redirect) v->name_error = my_strcpy(msg_redirect);
}

int error_management_pipe_and_redirect(sts *v, char *line)
{
    char **semi = str_to_word_array(line, ";");
    int error = 0;

    for (int i = 0; semi[i] && !error; i++) {
        check_pipe(v, semi[i], &error);
    }
    if (error)
        return (1);
    return (0);
}
