/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** parsing_buf
*/

#include "project.h"

static void clear_redirection(sts *v)
{
    v->redirect = NULL;
    v->redirect_dbl = NULL;
    v->rev_redirect = NULL;
    v->dbl_rev_redirect = NULL;
}

static void make_choice_run_command(sts *v, char *line)
{
    char **pipe = str_to_word_array(line, "|");
    if (pipe[1] != NULL) {
        get_num_pipes(v, line);
        create_command_pipe(v, pipe);
        run_piped_command(v->cmds, v);
        free_ll_cmd_line(v);
    } else if (pipe[1] == NULL && (v->redirect || v->redirect_dbl ||
    v->dbl_rev_redirect || v->rev_redirect)) {
        simple_cmd_redirect(v, line);
    } else {
        read_command(v, line);
    }
}

int parsing_buffer(sts *v, char *buffer)
{
    if (error_management_pipe_and_redirect(v, buffer))
        return (0);
    char **tab = str_to_word_array(buffer, ";");
    reformat_tab(tab);
    for (int i = 0; tab[i]; i++) {
        clear_redirection(v);
        check_redirection(v, tab[i]);
        make_choice_run_command(v, tab[i]);
    }
    return 0;
}
