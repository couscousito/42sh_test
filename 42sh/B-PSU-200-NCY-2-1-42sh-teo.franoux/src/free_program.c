/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** free_program
*/

#include "project.h"

void free_program(sts *v)
{
    free(v->username);
    if (v->my_env != NULL) free_str_to_word_array(v->my_env);
    free(v);
}
