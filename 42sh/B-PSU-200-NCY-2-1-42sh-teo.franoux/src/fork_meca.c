/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** fork_meca
*/

#include "project.h"


int segmentation_fault_management(sts *v, int status)
{
    char *segmentation = "Segmentation fault\n";
    char *core_dumped = "Segmentation fault (core dumped)\n";

    if (status == 139 || status == 11) {
        v->exit_code = 139;
        if (WCOREDUMP(status) > 0) {
            write(2, core_dumped, my_strlen(core_dumped));
            return 1;
        }
        if (write(2, segmentation, my_strlen(segmentation)) < 0)
            return 1;
        return 1;
    }
    return 0;
}

int floating_point_management(sts *v, int status)
{
    char *floating_point = "Floating exception\n";
    char *core_dumped = "Floating exception (core dumped)\n";

    if (status == 136 || status == 8) {
        v->exit_code = 136;
        if (WCOREDUMP(status) > 0) {
            write(2, core_dumped, my_strlen(core_dumped));
            return 1;
        }
        if (write(2, floating_point, my_strlen(floating_point)) < 0)
            return 1;
        return 1;
    }
    return 0;
}

int exec_format_error(sts *v, int status, char **command)
{
    char *format_error = ": Exec format error. Wrong Architecture.\n";
    if (WEXITSTATUS(status) == 255) {
        v->exit_code = 1;
        v->name_error = create_error_message(command[0], format_error);
        return 1;
    }
    return 0;
}

void management_error_fork_child(sts *v, int status, char **command)
{
    if (segmentation_fault_management(v, status)) return;
    if (floating_point_management(v, status)) return;
    if (exec_format_error(v, status, command)) return;
    v->exit_code = WEXITSTATUS(status);
}

void run_fork(sts *v, char *command, char **name_val)
{
    pid_t pid;
    int status;
    if ((pid = fork()) == -1) {
        perror("fork");
        return;
    } else if (pid == 0) {
        execve(command, name_val, v->my_env);
        exit(-1);
    } else {
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
        } else {
            management_error_fork_child(v, status, name_val);
        }
    }
}
