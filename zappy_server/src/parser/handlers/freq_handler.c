/*
** EPITECH PROJECT, 2025
** zappy_server [WSL: Ubuntu]
** File description:
** freq_handler
*/

#include "arguments.h"
#include <stdio.h>
#include <stdlib.h>

int freq_handler(int argc, char **argv, arguments_t *arguments,
    int index)
{
    if (index + 1 >= argc) {
        fprintf(stderr, "Error: -f expects <frequency>\n");
        return -1;
    }
    arguments->freq = atoi(argv[index + 1]);
    if (arguments->freq <= 0) {
        return -1;
    }
    return 1;
}
