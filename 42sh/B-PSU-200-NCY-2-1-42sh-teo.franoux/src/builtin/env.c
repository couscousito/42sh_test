/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** env
*/

#include "project.h"

void display_env(sts *v, char **name_val)
{
    int argc = len_dbl_array(name_val);

    (void) name_val;

    if (v->my_env == NULL) return;
    if (argc > 1) {
        v->name_error = env_fee_arguments_error(name_val);
        v->exit_code = 127;
        return;
    }
    for (int i = 0; v->my_env[i]; i++) {
        if (write(1, v->my_env[i], my_strlen(v->my_env[i])) < 0)
            return;
        if (write(1, "\n", 1) < 0)
            return;
    }
}

int found_environment_var(char *str, char *objet)
{
    for (int i = 0; str[i] != '='; i++) {
        if (str[i] != objet[i])
            return 0;
    }
    return 1;
}

int is_environment_var(sts *v, char **name_val)
{
    char *object = name_val[1];
    for (int i = 0; v->my_env[i]; i++) {
        if (found_environment_var(v->my_env[i], object))
            return 1;
    }
    return 0;
}

void fill_word_env(char *new, const char *old)
{
    int i = 0;
    for (; old[i]; i++){
        new[i] = old[i];
    }
    new[i] = '\0';
}
