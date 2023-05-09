/*
** EPITECH PROJECT, 2023
** init_project_langage_c
** File description:
** main
*/

#include "project.h"

void sig_handler(int signo)
{
    if (signo == SIGINT) {
        if (write(1, "\n$> ", 4) < 0)
            return;
    }
}

static void my_free_main(sts* v, int *exit_code)
{
    free_str_to_word_array(v->my_env);
    (*exit_code) = v->exit_code;
    free(v->my_home);
    free(v);
}

int exit_ctrl_d(sts *v, int len_size)
{
    char *msg = "exit\n";
    if (len_size == -1) {
        if (write(1, msg, my_strlen(msg)) < 0)
            return 1;
        v->exit_code = 1;
        return 1;
    }
    return 0;
}

void init_termios(void)
{
    struct termios mode_buffer,mode_direct;
    tcgetattr(STDOUT_FILENO, &mode_buffer);
    mode_direct = mode_buffer;
    mode_direct.c_oflag |= (ONLCR);
    tcsetattr(STDOUT_FILENO, TCSANOW, &mode_direct);
}

void display_linked_list(history_t *current)
{
    while (current != NULL) {
        printf("Current value: %s\n", current->command);
        if (current->prev != NULL) {
            printf("Previous value: %s\n", current->prev->command);
        }
        current = current->next;
    }
}

static void loop_getline(sts *v, char **env)
{
    char *line = NULL;
    v->command_index = 0;
    size_t len = 0;
    ssize_t len_size = 0;
    history_t *head = NULL;
    history_t *tail = NULL;
    initscr();
    init_termios();
    keypad(stdscr, TRUE);
    init(v, env);
    my_prompt(v);
    while ((len_size = ngetline(v, head, &line, &len)) != -1) {
        printf("\n");
        append_list(&head, &tail, line);
        if (exit_ctrl_d(v, len_size) == -1) break;
        if (parsing_buffer(v, line) == -1) break;
        if (v->name_error != NULL)
            error_management(v, len);
        if (v->stop) break;
        my_prompt(v);
        v->command_index++;
    }
    endwin();
    free(line);
}

int main(int argc, char *argv[], char **env)
{
    (void) argc;
    (void) argv;
    int exit_code;
    sts *v = malloc(sizeof(sts));
    v->cmds = NULL;
    signal(SIGINT, sig_handler);
    loop_getline(v, env);
    my_free_main(v, &exit_code);
    return exit_code;
}
