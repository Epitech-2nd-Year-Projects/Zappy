/*
** EPITECH PROJECT, 2025
** zappy_server [WSL: Ubuntu]
** File description:
** help_handler
*/

#include "arguments.h"
#include <stdlib.h>

int help_handler(int argc, char **argv, arguments_t *arguments,
    int index)
{
    (void)argc;
    (void)arguments;
    (void)index;
    print_usage(argv[0]);
    exit(EXIT_SUCCESS);
}
