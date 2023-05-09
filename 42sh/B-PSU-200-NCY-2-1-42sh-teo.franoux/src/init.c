/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** init
*/

#include "project.h"

void init_oldpwd(sts *v)
{
    char cwd[4096];
    int len_cwd;
    char **name_val = malloc(sizeof(char *) * 4);
    name_val[0] = malloc(sizeof(char) * 2);
    fill_word_env(name_val[0], " ");
    name_val[1] = malloc(sizeof(char) * 8);
    fill_word_env(name_val[1], "OLDPWD");
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        perror("getcwd() error");
    else {
        len_cwd = my_strlen(cwd);
        name_val[2] = malloc(sizeof(char) * (len_cwd + 1));
        fill_word_env(name_val[2], cwd);
        name_val[3] = NULL;
        my_setenv(v, name_val);
    }
}

void fill_my_env(sts *v, char **env)
{
    int total = len_dbl_array(env);
    v->my_env = malloc(sizeof(char *) * (total + 1));
    for (int i = 0; env[i]; i++) {
        v->my_env[i] = malloc(sizeof(char) * (my_strlen(env[i]) + 1));
        fill_word_env(v->my_env[i], env[i]);
    }
    v->my_env[total] = NULL;
}

void init(sts *v, char **env)
{
    fill_my_env(v, env);
    v->my_home = get_value_env_var(v, "HOME");
    v->exit_code = 0;
    v->stop = 0;
    v->name_error = NULL;
}
