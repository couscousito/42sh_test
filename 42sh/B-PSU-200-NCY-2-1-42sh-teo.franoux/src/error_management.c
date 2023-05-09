/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** error_management
*/

#include "project.h"

void error_management(sts *v, int len_line)
{
    for (int i = 0; v->name_error[i]; i++)
        if (write(2, &v->name_error[i], 1) < 0)
            return;
    if (v->name_error) free(v->name_error);
    v->name_error = NULL;
    if (len_line == -1 || isatty(0) != 0)
        v->exit_code = 0;
}
