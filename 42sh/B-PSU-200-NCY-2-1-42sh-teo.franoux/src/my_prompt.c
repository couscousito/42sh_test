/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** my_prompt
*/

#include "project.h"

char *extract_username(char *strline)
{
    const char *model = "USERNAME";
    char *word;
    int len_word = 0;
    for (int i = 0; i != 8; i++) {
        if (model[i] != strline[i])
            return NULL;
    }
    for (int l = 9; strline[l]; l++, len_word++);
    word = malloc(sizeof(char) * (len_word + 1));
    for (int k = 9; strline[k]; k++) {
        word[k - 9] = strline[k];
    }
    word[len_word] = '\0';
    return word;
}

void init_prompt(sts *v, char *env[])
{
    char *username;
    for (int i = 0; env[i]; i++) {
        if ((username = extract_username(env[i])) != NULL) {
            v->username = username;
            return;
        }
    }
}

void my_prompt(sts *v)
{
    (void) v;
    if (isatty(0) == 0)
        return;
    if (printw("$>") < 0)
        return;
}
