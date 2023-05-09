/*
** EPITECH PROJECT, 2023
** B-PSU-200-NCY-2-1-42sh-teo.franoux
** File description:
** ncurses_getline
*/

#include "../include/project.h"
#define ctrl(x)           ((x) & 0x1f)

static void back_space(char **char_ptr, int ch, int *len)
{
    int row;
    int col;
    if (ch == KEY_BACKSPACE) {
        getyx(stdscr, row, col);
        if (*len > 0) {
            (*len)--;
            (*char_ptr)[*len] = '\0';
            delch();
            move(row, col);
        }
        if (col < 2)
            move(row, 2);
    }
}

static int null_handle(char **char_ptr, size_t n_alloc, size_t *n)
{
    if (*char_ptr == NULL) {
        *char_ptr = malloc(n_alloc);
        if (*char_ptr == NULL)
            return -1;
        *n = n_alloc;
    }
    return 0;
}

char *realloc_memory(size_t *n, const size_t n_alloc, char **char_ptr)
{
    size_t n_realloc;
    char *temp;
    n_realloc = *n + n_alloc;
    temp = realloc(*char_ptr, n_realloc + 1);
    if (temp == NULL) return NULL;
    *char_ptr = temp;
    *n = n_realloc;
    return *char_ptr;
}

int history(sts *v, history_t *history, int ch, char **char_ptr)
{
    int row;
    int col;
    getyx(stdscr, row, col);
    if (ch == KEY_UP) {
        v->nbr_up++;
        if (history == NULL) return 1;
        move(row, 2);
        clrtoeol();
        if (v->command_index > 2) {
            for (int i = 0; i <= v->nbr_up; i++)
                history = history->prev;
        }
        *char_ptr = history->command;
        printw("%s", (*char_ptr));
        refresh();
    }
    if (ch == KEY_DOWN) {
        printf("down\n");
    }
}

int append_list(history_t **head, history_t **tail, char *command)
{
    history_t *node = malloc(sizeof(history_t));
    node->command = my_strcpy(command); 
    node->next = NULL;
    node->prev = *tail;
    if (*tail == NULL) {    
        (*head) = node;
        (*tail) = node;
    } else {
        (*tail)->next = node;
        (*tail) = node;
    }
}

int ngetline(sts *v, history_t *head, char **char_ptr, size_t *n)
{
    const size_t n_alloc  = sizeof(char);
    int ch;
    int len = 0;
    v->nbr_up = 0;
    if (char_ptr == NULL || n == NULL) return -1;
    if (null_handle(&(*char_ptr), n_alloc, &(*n)) == -1) return -1;
    while((ch = getch()) != '\n') {
        history(v, head, ch, &(*char_ptr));
        if (ch == ctrl('d')) return -1;
        if (ch != KEY_BACKSPACE) {
            *char_ptr = realloc_memory(&(*n), n_alloc, &(*char_ptr));
            (*char_ptr)[len] = (char) ch;
            len++;
        } else
            back_space(&(*char_ptr), ch, &len);
    } (*char_ptr)[len] = '\0';
    return len;
}