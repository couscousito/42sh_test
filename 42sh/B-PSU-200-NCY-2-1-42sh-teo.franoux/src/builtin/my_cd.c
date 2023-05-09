/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** my_cd
*/

#include "project.h"

void change_actual_pwd(sts *v, char *my_path, char *direct)
{
    char **name_val = malloc(sizeof(char *) * 4);
    char *pre_new = my_strcat(my_path, "/");
    char *new = my_strcat(pre_new, direct);
    free(pre_new);
    name_val[0] = malloc(sizeof(char) * 2);
    fill_word_env(name_val[0], " ");
    name_val[1] = malloc(sizeof(char) * 8);
    fill_word_env(name_val[1], "PWD");
    name_val[2] = malloc(sizeof(char) * (my_strlen(my_path) + 1));
    fill_word_env(name_val[2], new);
    name_val[3] = NULL;
    my_setenv(v, name_val);
}

int chech_env_home(sts *v, char *save_path)
{
    if (v->my_home == NULL) {
        v->name_error = my_strcpy("cd: No home directory.\n");
        v->exit_code = 1;
        free(save_path);
        return 0;
    }
    return 1;
}

int error_directory(sts *v, char **name_val, char *save_path)
{
    struct stat sb;
    char *error = ": Not a directory.\n";
    if (lstat(name_val[1], &sb) != -1) {
        if ((sb.st_mode & __S_IFMT) != __S_IFDIR) {
            v->name_error = create_error_message(name_val[1], error);
            v->exit_code = 1;
            free(save_path);
            return 1;
        }
    }
    return 0;
}
