/*
** EPITECH PROJECT, 2023
** B-PSU-200-NCY-2-1-42sh-teo.franoux
** File description:
** regex
*/

#ifndef REGEX_H
    #define REGEX_H

    #ifndef NULL
        #define NULL ((void *)0)
    #endif // !NULL

typedef struct Regex_String_Linked_List_s {
    char *string;
    int length;
    int pos;
    struct Regex_String_Linked_List_s *prev;
    struct Regex_String_Linked_List_s *next;
} regex_string_ll_t;

void delete_regex_string_node(regex_string_ll_t *node);
regex_string_ll_t *pop_regex_string_node(regex_string_ll_t **list,
regex_string_ll_t *node);
void push_regex_string_node(regex_string_ll_t **list, regex_string_ll_t *node);
regex_string_ll_t *new_regex_string_node(char *string);

#endif // !REGEX_H
