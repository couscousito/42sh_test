/*
** EPITECH PROJECT, 2023
** init_project_langage_c
** File description:
** my
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>

int my_strlen(const char *str);
void my_revstr(char *str);
int str_to_int(char *str);
int my_intlen(int num);
char *int_to_str(int n);
char **str_to_word_array(char *str, char *delimiters);
void free_str_to_word_array(char **str);
char *my_strcat(char *left, char *right);
int my_strcmp(char *f, char *s);
char *my_strcpy(const char *source);
