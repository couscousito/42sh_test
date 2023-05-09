/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** my_exit
*/

#include "project.h"

void my_exit(sts *v, char **name_val)
{
    int n_argument = len_dbl_array(name_val);
    if (v->exit_code != 0) {
        v->stop = 1;
        return;
    }
    if (n_argument == 2) {
        v->exit_code = str_to_int(name_val[1]);
    } else if (n_argument > 2) {
        v->exit_code = 1;
        v->name_error = my_strcpy("exit: too many arguments\n");
    } else
        v->exit_code = 0;
    if (n_argument < 3)
        v->stop = 1;
}
