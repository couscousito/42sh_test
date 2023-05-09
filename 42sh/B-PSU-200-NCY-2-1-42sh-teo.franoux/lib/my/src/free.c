/*
** EPITECH PROJECT, 2023
** my_library
** File description:
** free
*/

#include "my.h"

void free_str_to_word_array(char **str)
{
    for (int i = 0; str[i]; i++)
        free(str[i]);
    free(str);
}
