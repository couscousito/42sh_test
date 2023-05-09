/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** verif_cd_builtin
*/

#include "project.h"

int cd_option_checker(sts *v, char **name_val, int argc)
{
    if (argc == 1) return 0;
    if (name_val[1][1] == '\0' && argc == 2) return 0;
    if (name_val[1][0] == '-' && name_val[1][1] != 'l' && argc >= 2) {
        v->exit_code = 1;
        v->name_error = my_strcpy("Usage: cd [-plvn][-|<dir>].\n");
        return 1;
    }
    if (name_val[1][0] == '-' && name_val[1][1] == '\0') return 0;
    if (name_val[1][0] == '-' && name_val[1][1] == 'l' && argc == 2) {
        char *path = get_value_env_var(v, "HOME");
        if (write(1, path, my_strlen(path)) < 0)
            return 1;
        if (write(1, " \n", 2) < 0)
            return 1;
        free(path);
        return 1;
    }
    return 0;
}
