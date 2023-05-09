/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** buildin_fork_pipe
*/

#include "project.h"

int check_if_buildin_run(cmdLine *cmd)
{
    for (int i = 0; all_builtin[i].fct_name != NULL; i++) {
        if (my_strcmp(cmd->argv[0], all_builtin[i].fct_name) == 0) {
            return (1);
        }
    }
    return (0);
}

static void verif_exit_built_in(sts *v, int is_exit)
{
    if (is_exit)
        v->stop = 0;
}

static int set_exit_or_not(cmdLine *cmd)
{
    if (my_strcmp(cmd->argv[0], "exit") == 0) return (1);
    return (0);
}

int execute_buildin_fork_pipe(sts *v, cmdLine *cmd)
{
    int is_exit = 0;
    for (int i = 0; all_builtin[i].fct_name != NULL; i++) {
        if (my_strcmp(cmd->argv[0], all_builtin[i].fct_name) == 0) {
            is_exit = set_exit_or_not(cmd);
            all_builtin[i].my_function(v, cmd->argv);
            verif_exit_built_in(v, is_exit);
            return (1);
        }
    }
    return (0);
}
