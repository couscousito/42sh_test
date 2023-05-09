/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** setenv
*/

#include "project.h"

void modify_env_var(sts *v, char **name_val)
{
    for (int i = 0; v->my_env[i]; i++) {
        if (found_environment_var(v->my_env[i], name_val[1])) {
            free(v->my_env[i]);
            v->my_env[i] = create_my_env_variable(name_val);
        }
    }
}

void add_env_var(sts *v, char **name_val)
{
    int total = len_dbl_array(v->my_env);
    char **new = malloc(sizeof(char *) * (total + 2));
    for (int i = 0; v->my_env[i]; i++) {
        new[i] = malloc(sizeof(char) * (my_strlen(v->my_env[i]) + 1));
        fill_word_env(new[i], v->my_env[i]);
    }
    new[total] = create_my_env_variable(name_val);
    new[total + 1] = NULL;
    free_str_to_word_array(v->my_env);
    v->my_env = new;
}

void add_empty_env(sts *v, char **name_val)
{
    char **new = malloc(sizeof(char *) * 2);
    new[0] = create_my_env_variable(name_val);
    new[1] = NULL;
    v->my_env = new;
}

void my_setenv(sts *v, char **name_val)
{
    int argc = len_dbl_array(name_val);
    int is_in_env;
    if (alphanumeric_check(v, name_val[1]) == 0) return;
    if (v->my_env == NULL && argc > 1) {
        add_empty_env(v, name_val);
        return;
    }
    if (argc == 1) {
        display_env(v, name_val);
        return;
    }
    is_in_env = is_environment_var(v, name_val);
    if ((argc == 2 || argc == 3) && is_in_env)
        modify_env_var(v, name_val);
    if ((argc == 2 || argc == 3) && !is_in_env )
        add_env_var(v, name_val);
    free_str_to_word_array(name_val);
}
