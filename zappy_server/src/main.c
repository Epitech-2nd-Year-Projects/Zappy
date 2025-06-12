/*
** EPITECH PROJECT, 2025
** zappy_server [WSL: Ubuntu]
** File description:
** main
*/

#include <stdlib.h>

#include "arguments.h"
#include "constants.h"
#include "server.h"

int main(int argc, char **argv)
{
    arguments_t arguments;

    if (!parse_args(argc, argv, &arguments)) {
        free_arguments(&arguments);
        return EXIT_ERROR;
    }
    if (run_server(&arguments) == EXIT_ERROR) {
        free_arguments(&arguments);
        return EXIT_ERROR;
    }
    free_arguments(&arguments);
    return EXIT_SUCCESS;
}
