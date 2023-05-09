/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** unsetenv
*/

#include "project.h"

void delete_env_var(sts *v, char *var)
{
    int j = 0;
    int total = len_dbl_array(v->my_env);
    char **new = malloc(sizeof(char *) * (total));
    for (int i = 0; v->my_env[i]; i++, j++) {
        if (!found_environment_var(v->my_env[i], var)) {
            new[j] = malloc(sizeof(char) * (my_strlen(v->my_env[i]) + 1));
            fill_word_env(new[j], v->my_env[i]);
        } else {
            j--;
        }
    }
    new[total - 1] = NULL;
    free_str_to_word_array(v->my_env);
    v->my_env = new;
}

int environment_var_in(sts *v, char *objet)
{
    for (int i = 0; v->my_env[i]; i++) {
        if (found_environment_var(v->my_env[i], objet))
            return 1;
    }
    return 0;
}

void my_unsetenv(sts *v, char **name_val)
{
    if (len_dbl_array(name_val) == 1) {
        v->name_error = my_strcpy("unsetenv: Too few arguments.\n");
        v->exit_code = 1;
        return;
    }
    for (int i = 1; name_val[i]; i++) {
        if (environment_var_in(v, name_val[i]))
            delete_env_var(v, name_val[i]);
    }

}
