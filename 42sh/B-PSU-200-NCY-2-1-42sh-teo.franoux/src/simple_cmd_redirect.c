/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** simple_cmd_redirect
*/

#include "project.h"

static void simple_cmd_output(sts *v)
{
    int fd = -1;
    if (v->redirect) {
        fd = open(v->redirect, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        dup2(fd, 1);
        close(fd);
    }
    if (v->redirect_dbl) {
        fd = open(v->redirect_dbl, O_WRONLY | O_CREAT | O_APPEND, 0666);
        dup2(fd, 1);
        close(fd);
    }
}

static void input_cmd_simple(sts *v)
{
    int fd = -1;
    if (v->rev_redirect) {
        fd = open(v->rev_redirect, O_RDONLY, 0666);
        if (fd < 0) {
            perror("open");
            return;
        }
        dup2(fd, 0);
        close(fd);
    }
}

void simple_cmd_redirect(sts *v, char *cmd)
{
    int fd_out = dup(1);
    int fd_in = dup(0);
    simple_cmd_output(v);
    input_cmd_simple(v);
    read_command(v, cmd);
    if (v->redirect || v->redirect_dbl)
        dup2(fd_out, 1);
    if (v->rev_redirect)
        dup2(fd_in, 0);
}

void command_redirect_pipe(sts *v, cmdLine *cmd)
{
    int fd = -1;
    if (cmd->next != NULL) return;
    if (v->redirect) {
        fd = open(v->redirect, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        dup2(fd, 1);
        close(fd);
    }
    if (v->redirect_dbl) {
        fd = open(v->redirect_dbl, O_WRONLY | O_CREAT | O_APPEND, 0666);
        dup2(fd, 1);
        close(fd);
    }
}
