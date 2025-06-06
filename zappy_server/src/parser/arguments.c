/*
** EPITECH PROJECT, 2025
** zappy_server [WSL: Ubuntu]
** File description:
** args_parser
*/

#include "constants.h"
#include "arguments.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static int handle_argument(int argc, char **argv, arguments_t *arguments,
    int index)
{
    for (int i = 0; HANDLERS[i].argument_name != NULL; i++) {
        if (strcmp(argv[index], HANDLERS[i].argument_name) == 0) {
            return HANDLERS[i].handler(argc, argv, arguments, index);
        }
    }
    return -1;
}

void print_usage(const char *prog_name)
{
    printf(USAGE_MSG_1, prog_name);
    printf(USAGE_MSG_2);
}

bool parse_args(int argc, char *argv[], arguments_t *arguments)
{
    int skip = 0;

    arguments->port = -1;
    arguments->width = -1;
    arguments->height = -1;
    arguments->team_count = 0;
    arguments->team_names = NULL;
    arguments->clients = -1;
    arguments->freq = -1;
    for (int i = 1; i < argc; i++) {
        skip = handle_argument(argc, argv, arguments, i);
        if (skip < 0) {
            fprintf(stderr, "Error: Invalid argument '%s'\n", argv[i]);
            return false;
        }
        i += skip;
    }
    return true;
}

void free_arguments(arguments_t *arguments)
{
    if (arguments->team_names != NULL) {
        for (int i = 0; i < arguments->team_count; i++) {
            free(arguments->team_names[i]);
        }
        free(arguments->team_names);
    }
    arguments->team_names = NULL;
}
