/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** my_cd_builtin
*/

#include "project.h"

void change_oldpwd(sts *v, char *my_path)
{
    char **name_val = malloc(sizeof(char *) * 4);
    name_val[0] = malloc(sizeof(char) * 2);
    fill_word_env(name_val[0], " ");
    name_val[1] = malloc(sizeof(char) * 8);
    fill_word_env(name_val[1], "OLDPWD");
    name_val[2] = malloc(sizeof(char) * (my_strlen(my_path) + 1));
    fill_word_env(name_val[2], my_path);
    name_val[3] = NULL;
    my_setenv(v, name_val);
    free(my_path);
}

int cd_oldpwd(sts *v, char **name_val, int argc)
{
    char *oldpwd = get_value_env_var(v, "OLDPWD");
    char *save_path = get_actual_path();
    if (oldpwd == NULL || argc == 1) {
        free(save_path);
        free(oldpwd);
        return 0;
    }
    if (my_strcmp(name_val[1], "-") == 0) {
        if (chdir(oldpwd) != 0) {
            perror("cd");
            free(save_path);
            free(oldpwd);
            return 0;
        }
        change_oldpwd(v, save_path);
        free(oldpwd);
        return 1;
    }
    free(save_path); free(oldpwd);
    return 0;
}

static int cd_home_user(sts *v, char **name_val, int argc)
{
    char *save_path = get_actual_path();
    if (chech_env_home(v, save_path) == 0) return 0;
    if (argc == 1 || my_strcmp(name_val[1], "~") == 0) {
        if (chdir(v->my_home) != 0) {
            perror("cd");
            v->exit_code = 1;
            free(save_path);
            return 0;
        }
        change_oldpwd(v, save_path);
        return 1;
    }
    free(save_path);
    return 0;
}

static int cd_other_path(sts *v, char **name_val, int argc)
{
    char *save_path = get_actual_path();
    char *error_msg = ": No such file or directory.\n";
    int i = 1;
    if (argc == 1 || name_val[1][0] == '~' || name_val[1][1] == '\0') {
        free(save_path);
        return 0;
    }
    while (name_val[i][0] == '-') i++;
    if (chdir(name_val[i]) != 0) {
        if (error_directory(v, name_val, save_path)) return 0;
        v->name_error = create_error_message(name_val[i], error_msg);
        v->exit_code = 1;
        free(save_path);
        return 0;
    }
    change_oldpwd(v, save_path);
    return 1;
}

void change_directory(sts *v, char **name_val)
{
    int argc = len_dbl_array(name_val);
    if (cd_option_checker(v, name_val, argc) == 1) return;
    if (argc > 2) {
        if (name_val[1][0] != '-') {
            v->name_error = my_strcpy("cd: Too many arguments.\n");
            v->exit_code = 1;
            return;
        }
    }
    cd_home_user(v, name_val, argc);
    cd_oldpwd(v, name_val, argc);
    cd_other_path(v, name_val, argc);
}
