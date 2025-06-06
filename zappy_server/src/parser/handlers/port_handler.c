/*
** EPITECH PROJECT, 2025
** zappy_server [WSL: Ubuntu]
** File description:
** port_handler
*/

#include "arguments.h"
#include <stdio.h>
#include <stdlib.h>

int port_handler(int argc, char **argv, arguments_t *arguments,
    int index)
{
    if (index + 1 >= argc) {
        fprintf(stderr, "Error: -p expects <port>\n");
        return -1;
    }
    arguments->port = atoi(argv[index + 1]);
    if (arguments->port <= 0 || arguments->port > 65535) {
        return -1;
    }
    return 1;
}
