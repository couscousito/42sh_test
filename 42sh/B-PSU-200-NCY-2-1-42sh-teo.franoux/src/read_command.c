/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** read_command
*/

#include "project.h"

int check_sub_command(sts *v, char **name_val)
{
    struct stat sb;
    stat(name_val[0], &sb);
    if ((sb.st_mode & __S_IFMT) == __S_IFDIR) {
        v->name_error = name_val[0];
        v->name_error = my_strcat(v->name_error, ": Is a directory\n");
        v->exit_code = 126;
        return 0;
    }
    return 1;
}

int read_command(sts *v, char *line)
{
    v->exit_code = 0;
    char **tab = str_to_word_array(line, " \t");
    if (my_strlen(line) == 0) {
        free_str_to_word_array(tab);
        return 1;
    }
    for (int i = 0; all_builtin[i].fct_name != NULL; i++) {
        if (my_strcmp(tab[0], all_builtin[i].fct_name) == 0) {
            all_builtin[i].my_function(v, tab);
            return 1;
        }
    }
    run_function(v, tab);
    free_str_to_word_array(tab);
    return 1;
}
