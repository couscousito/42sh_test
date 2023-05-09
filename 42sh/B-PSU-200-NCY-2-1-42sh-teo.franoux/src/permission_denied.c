/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** permission_denied
*/

#include "project.h"

int permission_denied_folder(sts *v, char **name_val)
{
    struct stat sb;
    if (lstat(name_val[0], &sb) != -1 && (sb.st_mode & S_IFMT) == S_IFDIR) {
        v->name_error = my_strcat(name_val[0], ": Permission denied.\n");
        v->exit_code = 1;
        return 1;
    }
    return 0;
}

int perm_denied_exec(sts *v, char **name_val)
{
    struct stat sb;
    if (lstat(name_val[0], &sb) != -1 &&
    (sb.st_mode & S_IFMT) == S_IFREG && !(sb.st_mode & S_IXOTH)) {
        v->name_error = my_strcat(name_val[0], ": Permission denied.\n");
        v->exit_code = 1;
        return 1;
    }
    return 0;
}
