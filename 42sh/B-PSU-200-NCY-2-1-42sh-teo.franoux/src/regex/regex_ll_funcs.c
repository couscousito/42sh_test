/*
** EPITECH PROJECT, 2023
** regex
** File description:
** regex_ll_funcs
*/

#include "regex.h"
#include "stdlib.h"

static int regex_strlen(char *string)
{
    int i = 0;

    if (string == NULL)
        return (0);
    while (string[i] != '\0')
        i++;
    return (i);
}

regex_string_ll_t *new_regex_string_node(char *string)
{
    regex_string_ll_t *node = malloc(sizeof(regex_string_ll_t));

    if (node == NULL)
        return (NULL);
    *node = (regex_string_ll_t){0};
    node->string = string;
    node->length = regex_strlen(string);
    node->prev = NULL;
    node->next = NULL;
    node->pos = 0;
    return (node);
}

void push_regex_string_node(regex_string_ll_t **list, regex_string_ll_t *node)
{
    regex_string_ll_t *tmp = *list;

    if (node == NULL)
        return;
    if (*list == NULL) {
        *list = node;
        node->prev = NULL;
        node->next = NULL;
        return;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = node;
    node->prev = tmp;
    node->next = NULL;
}

regex_string_ll_t *pop_regex_string_node(regex_string_ll_t **list,
regex_string_ll_t *node)
{
    regex_string_ll_t *tmp = *list;

    if (node == NULL)
        return (NULL);
    if (*list == NULL)
        return (NULL);
    if (node == *list) {
        *list = node->next;
        if (*list != NULL)
            (*list)->prev = NULL;
        return (node);
    }
    while (tmp != NULL && tmp != node)
        tmp = tmp->next;
    if (tmp == NULL)
        return (NULL);
    tmp->prev->next = tmp->next;
    if (tmp->next != NULL)
        tmp->next->prev = tmp->prev;
    return (tmp);
}

void delete_regex_string_node(regex_string_ll_t *node)
{
    if (node == NULL)
        return;
    free(node->string);
    free(node);
}
