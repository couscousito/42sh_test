/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** env_tools
*/

#include "project.h"

char *create_my_env_variable(char **name_val)
{
    int total = my_strlen(name_val[1]) + 1;
    int j = 0;
    char *new;
    if (name_val[2])
        total += my_strlen(name_val[2]);
    new = malloc(sizeof(char) * (total + 1));
    for (int i = 0; name_val[1][i]; i++, j++)
        new[j] = name_val[1][i];
    new[j++] = '=';
    if (name_val[2])
        for (int p = 0; name_val[2][p]; p++, j++)
            new[j] = name_val[2][p];
    new[j] = '\0';
    return new;
}

char *extract_value_env_var(char *env_var)
{
    int start = 0;
    int len_total = 0;
    int j = 0;
    for (; env_var[start] != '='; start++);
    len_total = my_strlen(env_var) - start - 1;
    if (len_total == 0) return NULL;
    char *new = malloc(sizeof(char) * (len_total + 1));
    for (int i = start + 1; env_var[i]; i++, j++) {
        new[j] = env_var[i];
    }
    new[len_total] = '\0';
    return new;
}

char *get_value_env_var(sts *v, char *name_var)
{
    for (int i = 0; v->my_env[i]; i++) {
        if (found_environment_var(v->my_env[i], name_var)) {
            return extract_value_env_var(v->my_env[i]);
        }
    }
    return NULL;
}
