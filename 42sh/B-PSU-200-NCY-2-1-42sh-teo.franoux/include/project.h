/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** project
*/

#pragma once

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <ncurses.h>
#include <termios.h>

typedef struct cmdLine {
    char *command;
    char **argv;
    struct cmdLine *next;
} cmdLine;

typedef struct suitecase {
    char *username;
    char **my_env;
    char **my_path;
    char *name_error;
    char *my_home;
    int exit_code;
    int stop;
    cmdLine *cmds;
    int numPipes;
    int *pipefds;
    int j;
    char *redirect;
    char *redirect_dbl;
    char *rev_redirect;
    char *dbl_rev_redirect;
    int command_index;
    int nbr_up;
} sts;

typedef struct builtin_s {
    char* fct_name;
    void (*my_function)(sts *v, char **name_val);
} builtin_t;

typedef struct history_s {
    char *command;
    struct history_s *next;
    struct history_s *prev;
} history_t;

void init(sts *v, char **env);
void init_prompt(sts *v, char *env[]);
void free_program(sts *v);
void my_prompt(sts *v);
int read_command(sts *v, char *line);
void change_directory(sts *v, char **name_val);
int cd_option_checker(sts *v, char **name_val, int argc);
int error_directory(sts *v, char **name_val, char *save_path);

int len_dbl_array(char **tab);
void my_exit(sts *v, char **name_val);
void error_management(sts *v, int len_line);
int run_function(sts *v, char **name_val);

void display_env(sts *v, char **name_val);
void my_setenv(sts *v, char **name_val);
void my_unsetenv(sts *v, char **name_val);
int is_environment_var(sts *v, char **name_val);
char *create_my_env_variable(char **name_val);
void fill_word_env(char *new, const char *old);
int found_environment_var(char *str, char *objet);
char *extract_value_env_var(char *env_var);
char *get_actual_path(void);
char *check_good_val_env_path(sts *v, char **path_var, char **name_val);
char *my_strrcv(char *string, char stopper);
char **get_path_access(char *PATH_line);
char **retrieve_path_executable(sts *v, char **name_val);
char *path_executable_with_name(char *path, char *name);
int permission_denied_folder(sts *v, char **name_val);
int perm_denied_exec(sts *v, char **name_val);


void change_directory(sts *v, char **name_val);
char *get_value_env_var(sts *v, char *name_var);

void run_fork(sts *v, char *command, char **name_val);
int exec_format_verif(char **name_val);

char *create_error_message(char *name, char *error);
int alphanumeric_check(sts *v, char *str);
char *env_fee_arguments_error(char **name_val);

int chech_env_home(sts *v, char *save_path);
int parsing_buffer(sts *v, char *buf);
void reformat_tab(char **tab);
int create_command_pipe(sts *v, char **pipe);
void free_ll_cmd_line(sts *v);
void run_piped_command(cmdLine* command, sts *v);
char *find_executable_in_path(sts *v, char **name_val);

static const builtin_t all_builtin[] = {
    {"cd", change_directory},
    {"env", display_env},
    {"setenv", my_setenv},
    {"unsetenv", my_unsetenv},
    {"exit", my_exit},
    {NULL, NULL}
};

int check_if_buildin_run(cmdLine *cmd);
int execute_buildin_fork_pipe(sts *v, cmdLine *cmd);
void create_pipes(sts *v);
int my_strlen(const char *str);
void my_revstr(char *str);
int str_to_int(char *str);
int my_intlen(int num);
char *int_to_str(int n);
char **str_to_word_array(char *str, char *delimiters);
void free_str_to_word_array(char **str);
char *my_strcat(char *left, char *right);
int my_strcmp(char *f, char *s);
char *my_strcpy(const char *source);
int check_redirection(sts *v, char *cmd);
char *copy_str_n(char *str, int start);
void simple_cmd_redirect(sts *v, char *cmd);
void command_redirect_pipe(sts *v, cmdLine *cmd);
void change_actual_pwd(sts *v, char *my_path, char *direct);
void get_num_pipes(sts *v, char *line);
int error_management_pipe_and_redirect(sts *v, char *line);
int ngetline(sts *v, history_t *head, char **char_ptr, size_t *n);
int append_list(history_t **head, history_t **tail, char *command);
