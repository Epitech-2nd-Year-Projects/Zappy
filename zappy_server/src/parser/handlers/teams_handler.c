/*
** EPITECH PROJECT, 2025
** zappy_server [WSL: Ubuntu]
** File description:
** teams_handler
*/

#include "arguments.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_option(const char *str)
{
    return str[0] == '-' && str[1] != '\0';
}

static int fill_team_names(int count, arguments_t *arguments, char **argv)
{
    arguments->team_count = count;
    arguments->team_names = calloc((size_t)(arguments->team_count + 1),
        sizeof(char *));
    if (arguments->team_names == NULL) {
        perror("malloc");
        exit(EXIT_ERROR);
    }
    for (int i = 0; i < count; i++) {
        arguments->team_names[i] = strdup(argv[i]);
        if (arguments->team_names[i] == NULL) {
            perror("strdup");
            free_arguments(arguments);
            exit(EXIT_ERROR);
        }
    }
    return count;
}

int teams_handler(int argc, char **argv, arguments_t *arguments,
    int index)
{
    int start = index + 1;
    int count = 0;

    while (start + count < argc && !is_option(argv[start + count])) {
        count++;
    }
    if (count == 0) {
        fprintf(stderr, "Error: -n expects at least one team name\n");
        return -1;
    }
    return fill_team_names(count, arguments, argv + start);
}
