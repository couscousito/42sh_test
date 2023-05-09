/*
** EPITECH PROJECT, 2023
** init_project_langage_c
** File description:
** my_strlen
*/

int my_strlen(const char *str)
{
    int i = 0;
    for (; str[i]; i++);
    return i;
}

void my_revstr(char *str)
{
    int len_str = my_strlen(str);
    int index = len_str - 1;
    char temp;
    for (int i = 0; i < len_str / 2; i++) {
        temp = str[i];
        str[i] = str[index];
        str[index--] = temp;
    }
}

int str_to_int(char *str)
{
    int num = 0;
    for (int i = 0; str[i]; i++) {
        num *= 10;
        num += (str[i] - 48);
    }
    return num;
}
