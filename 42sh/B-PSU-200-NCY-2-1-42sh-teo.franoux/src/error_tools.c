/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** error_tools
*/

#include "project.h"

char *create_error_message(char *name, char *error)
{
    int total = my_strlen(name) + my_strlen(error);
    int j = 0;
    char *new = malloc(sizeof(char) * (total + 1));
    for (int i = 0; name[i]; i++, j++)
        new[j] = name[i];
    for (int i = 0; error[i]; i++, j++)
        new[j] = error[i];
    new[total] = '\0';
    return new;
}

char *env_fee_arguments_error(char **name_val)
{
    int total = my_strlen(name_val[0]);
    int j = 0;
    if (name_val[1]) total += my_strlen(name_val[1]);
    char *msg = malloc(sizeof(char) * (total + 1));
    char *final;
    for (int i = 0; name_val[0][i]; i++, j++)
        msg[j] = name_val[0][i];
    for (int i = 0; name_val[1][i]; i++, j++)
        msg[j] = name_val[1][i];
    msg[j] = '\0';
    final = create_error_message(msg, ": No such file or directory");
    free(msg);
    return final;
}
