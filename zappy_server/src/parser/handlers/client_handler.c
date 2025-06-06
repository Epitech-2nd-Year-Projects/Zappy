/*
** EPITECH PROJECT, 2025
** zappy_server [WSL: Ubuntu]
** File description:
** client_handler
*/

#include "arguments.h"
#include <stdio.h>
#include <stdlib.h>

int clients_handler(int argc, char **argv, arguments_t *arguments,
    int index)
{
    if (index + 1 >= argc) {
        fprintf(stderr, "Error: -c expects <clients>\n");
        return -1;
    }
    arguments->clients = atoi(argv[index + 1]);
    if (arguments->clients <= 0) {
        return -1;
    }
    return 1;
}
