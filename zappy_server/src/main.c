/*
** EPITECH PROJECT, 2025
** zappy_server [WSL: Ubuntu]
** File description:
** main
*/

#include <stdlib.h>
#include <stdio.h>

#include "arguments.h"
#include "constants.h"
#include "server.h"

static bool validate_arguments(const arguments_t *args)
{
    if (args->port <= 0 || args->port > 65535) {
        return fprintf(stderr, "Error: Invalid port number\n"), false;
    }
    if (args->width <= 0) {
        return fprintf(stderr, "Error: Width must be positive\n"), false;
    }
    if (args->height <= 0) {
        return fprintf(stderr, "Error: Height must be positive\n"), false;
    }
    if (args->team_count <= 0) {
        return fprintf(stderr, "Error: At least one team required\n"), false;
    }
    if (args->clients <= 0) {
        return fprintf(stderr, "Error:"
                               " Clients number must be positive\n"), false;
    }
    if (args->freq <= 0) {
        return fprintf(stderr, "Error: Frequency must be positive\n"), false;
    }
    return true;
}

int main(int argc, char **argv)
{
    arguments_t arguments;

    if (!parse_args(argc, argv, &arguments)) {
        free_arguments(&arguments);
        return EXIT_ERROR;
    }

    if (!validate_arguments(&arguments)) {
        free_arguments(&arguments);
        print_usage(argv[0]);
        return EXIT_ERROR;
    }

    if (run_server(&arguments) == EXIT_ERROR) {
        free_arguments(&arguments);
        return EXIT_ERROR;
    }
    free_arguments(&arguments);
    return EXIT_SUCCESS;
}