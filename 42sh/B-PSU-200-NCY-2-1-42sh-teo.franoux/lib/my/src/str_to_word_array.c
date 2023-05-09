/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** str_to_word_array
*/

#include "my.h"

int deliter(char c, char *delimiters, int l)
{
    for (int i = 0; delimiters[i]; i++) {
        if (delimiters[i] == c && l == 0)
            return 1;
        if ((delimiters[i] == c || c == '\0') && l == 1)
            return 0;
    }
    if (l == 0)
        return 0;
    if (l == 1)
        return 1;
    return 0;
}

int count_word(char *str, char *delimiters)
{
    int lever = 0;
    int count = 0;
    for (int i = 0; str[i]; i++) {
        if ((deliter(str[i], delimiters, 0) && lever == 0) || i == 0) {
            lever = 1;
        }
        if (deliter(str[i], delimiters, 1) && lever == 1) {
            count++;
            lever = 0;
        }
    }
    return count;
}

int l_word_p(char *str, char *delimiter, int *index)
{
    int len = 0;
    int in = *index;
    while (deliter(str[in], delimiter, 0)) {
        *index += 1;
        in++;
    }
    while (deliter(str[in], delimiter, 1)) {
        in += 1;
        len++;
    }
    return len;
}

char *get_word(char *str, int *index, int len)
{
    int stop = *index + len;
    int j = 0;
    char *word = malloc(sizeof(char) * (len + 1));
    for (int i = *index; i < stop; i++, j++) {
        word[j] = str[*index];
        *index += 1;
    }
    *index += 1;
    word[j] = '\0';
    return word;
}

char **str_to_word_array(char *str, char *delimiters)
{
    int n_word = count_word(str, delimiters);
    int index = 0;
    int size_new_word = 0;
    char **new = malloc(sizeof(char *) * (n_word + 1));
    new[n_word] = NULL;
    for (int i = 0; i < n_word; i++) {
        size_new_word = l_word_p(str, delimiters, &index);
        new[i] = get_word(str, &index, size_new_word);
    }
    return new;
}
