/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** tools_verif
*/

#include "project.h"

int len_dbl_array(char **tab)
{
    int i = 0;
    for (; tab[i]; i++);
    return i;
}

int exec_format_verif(char **name_val)
{
    if (name_val[0][0] == '.' && name_val[0][1] == '/')
        return 1;
    return 0;
}

static int first_letter_var_setenv_error(sts *v)
{
    const char *error = "setenv: Variable name must begin with a letter.\n";
    v->name_error = my_strcpy(error);
    v->exit_code = 1;
    return 0;
}

int alphanumeric_check(sts *v, char *str)
{
    int val = 1;
    char *err = ": Variable name must contain alphanumeric characters.\n";
    if (str == NULL) return 1;
    if ((str[0] > 90 || str[0] < 65) && (str[0] > 122 || str[0] < 97))
        return first_letter_var_setenv_error(v);
    if (str == NULL) return 1;
    for (int i = 0; str[i]; i++) {
        if ((str[i] < 48 || str[i] > 57) && (str[i] < 65 || str[i] > 90) &&
        (str[i] < 97 || str[i] > 122))
            val = 0;
    }
    if (val == 0) {
        v->name_error = create_error_message("setenv", err);
        v->exit_code = 1;
        return 0;
    }
    return 1;
}
