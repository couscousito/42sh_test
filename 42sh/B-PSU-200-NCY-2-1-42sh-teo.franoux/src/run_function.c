/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** run_function
*/

#include "project.h"

char *my_strrcv(char *string, char stopper)
{
    int len = 0;
    char *new_w;
    for (; string[len] != stopper; len++);
    new_w = malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; i++)
        new_w[i] = string[i];
    new_w[len] = '\0';
    return new_w;
}

char *my_str_remove_start(char *str, char *str_to_del)
{
    int len_str_d = my_strlen(str_to_del);
    int len_str = my_strlen(str);
    if (len_str_d >= len_str) return NULL;
    char *new = malloc(sizeof(char) * (len_str - len_str_d + 1));
    for (int i = len_str_d; str[i]; i++) {
        new[i - len_str_d] = str[i];
    }
    new[len_str - len_str_d] = '\0';
    return new;
}

char **get_path_access(char *PATH_line)
{
    char *new_path = my_str_remove_start(PATH_line, "PATH=");
    char **new = str_to_word_array(new_path, ":");
    free(new_path);
    return new;
}

char *find_executable_in_path(sts *v, char **name_val)
{
    char *path_env_value = get_value_env_var(v, "PATH");
    char **path_var = NULL;
    char *new_path = NULL;
    if (path_env_value == NULL) return NULL;
    path_var = str_to_word_array(path_env_value, ":");
    free(path_env_value);
    for (int i = 0; path_var[i]; i++) {
        new_path = path_executable_with_name(path_var[i], name_val[0]);
        if (access(new_path, X_OK) == 0) {
            free_str_to_word_array(path_var);
            return new_path;
        }
        free(new_path);
    }
    free_str_to_word_array(path_var);
    return NULL;
}

int run_function(sts *v, char **name_val)
{
    char *result = NULL;
    int format_executable = exec_format_verif(name_val);
    if (permission_denied_folder(v, name_val) == 1) return 0;
    if (perm_denied_exec(v, name_val)) return 0;
    if (access(name_val[0], X_OK) == 0 ||
    (format_executable && access(name_val[0], F_OK) == 0)) {
        result = name_val[0];
        run_fork(v, result, name_val);
        return 0;
    }
    if ((result = find_executable_in_path(v, name_val)) == NULL) {
        v->name_error = my_strcat(name_val[0], ": Command not found.\n");
        v->exit_code = 1;
        return 0;
    }
    run_fork(v, result, name_val);
    free(result);
    return 0;
}
