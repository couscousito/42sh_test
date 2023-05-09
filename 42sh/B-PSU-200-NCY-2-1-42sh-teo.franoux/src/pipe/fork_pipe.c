/*
** EPITECH PROJECT, 2023
** bs-minishell2
** File description:
** test
*/

#include "project.h"

static int child_process(cmdLine *command, sts *v, char *result)
{
    command_redirect_pipe(v, command);
    if (command->next){
        if (dup2(v->pipefds[v->j + 1], 1) < 0){
            perror("dup2");
            return (-1);
        }
    }
    if (v->j != 0){
        if (dup2(v->pipefds[v->j - 2], 0) < 0){
            perror(" dup2");
            return (-1);
        }
    }
    for (int i = 0; i < 2 * v->numPipes; i++)
        close(v->pipefds[i]);
    if (execve(result, command->argv, v->my_env) < 0 ){
        perror(command->command);
        exit(1);
    }
    exit(1);
}

static int run_my_buildin_fork(sts *v, cmdLine *cmd)
{
    int fd_out = dup(1);
    int fd_in = dup(0);
    if (cmd->next){
        if (dup2(v->pipefds[v->j + 1], 1) < 0){
            perror("dup2");
            return (-1);
        }
    }
    if (v->j != 0){
        if (dup2(v->pipefds[v->j - 2], 0) < 0){
            perror(" dup2");
            return (-1);
        }
    }
    if (v->j != 0) close(v->pipefds[v->j - 2]);
    execute_buildin_fork_pipe(v, cmd);
    if (cmd->next) close(v->pipefds[v->j + 1]);
    if (v->j != 0) dup2(fd_in, 0);
    if (cmd->next) dup2(fd_out, 1);
    return (2);
}

char *check_find_executable_pipe(sts *v, cmdLine *cmd)
{
    char *result = NULL;
    char *msg = ": Command not found.\n";

    if (check_if_buildin_run(cmd)) {
        run_my_buildin_fork(v, cmd);
        return NULL;
    }
    if (access(cmd->argv[0], X_OK) == 0) return (cmd->argv[0]);
    if ((result = find_executable_in_path(v, cmd->argv)) == NULL) {
        if (write(2, cmd->argv[0], my_strlen(cmd->argv[0])) < 0)
            return (NULL);
        if (write(2, msg, my_strlen(msg)) < 0)
            return (NULL);
        v->exit_code = 1;
        return NULL;
    }
    return (result);
}

static void sub_process_fork_child(sts *v, cmdLine *cmd)
{
    char *result = NULL;
    pid_t pid;
    result = check_find_executable_pipe(v, cmd);
    if (result != NULL) {
        if ((pid = fork()) < 0) {
            perror("error");
            return;
        }
        if (pid == 0)
            child_process(cmd, v, result);
    }
}

void run_piped_command(cmdLine* command, sts *v)
{
    int status;
    create_pipes(v);
    v->j = 0;
    while (command) {
        sub_process_fork_child(v, command);
        if (v->j != 0) close(v->pipefds[v->j - 2]);
        if (command->next) close(v->pipefds[v->j + 1]);
        command = command->next;
        v->j += 2;
    }
    for (int i = 0; i < v->numPipes + 1; i++)
        wait(&status);
}
