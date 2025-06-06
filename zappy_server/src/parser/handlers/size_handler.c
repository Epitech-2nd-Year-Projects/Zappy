/*
** EPITECH PROJECT, 2025
** zappy_server [WSL: Ubuntu]
** File description:
** size_handler
*/

#include "arguments.h"
#include <stdio.h>
#include <stdlib.h>

int width_handler(int argc, char **argv, arguments_t *arguments,
    int index)
{
    if (index + 1 >= argc) {
        fprintf(stderr, "Error: -x expects <width>\n");
        return -1;
    }
    arguments->width = atoi(argv[index + 1]);
    if (arguments->width <= 0) {
        return -1;
    }
    return 1;
}

int height_handler(int argc, char **argv, arguments_t *arguments,
    int index)
{
    if (index + 1 >= argc) {
        fprintf(stderr, "Error: -y expects <height>\n");
        return -1;
    }
    arguments->height = atoi(argv[index + 1]);
    if (arguments->height <= 0) {
        return -1;
    }
    return 1;
}
