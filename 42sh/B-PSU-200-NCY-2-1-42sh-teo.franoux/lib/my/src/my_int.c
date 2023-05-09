/*
** EPITECH PROJECT, 2023
** my_library
** File description:
** my_int
*/

#include "my.h"

int my_intlen(int num)
{
    int i = 0;
    for (; num != 0; num /= 10, i++);
    return i;
}

char *int_to_str(int n)
{
    int len_n = my_intlen(n);
    char *new = malloc(sizeof(char) * (len_n + 1));
    for (int i = len_n; i > 0; i--) {
        new[i - 1] = (n % 10) + 48;
        n = n / 10;
    }
    new[len_n] = '\0';
    return new;
}
