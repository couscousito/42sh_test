/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** pwd_tools
*/

#include "project.h"

char *get_actual_path(void)
{
    char cwd[4096];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        return NULL;
    }
    return my_strcpy(cwd);
}
