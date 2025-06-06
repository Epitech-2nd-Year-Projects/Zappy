/*
** EPITECH PROJECT, 2025
** zappy_server [WSL: Ubuntu]
** File description:
** main
*/

#include "arguments.h"

int main(int argc, char **argv)
{
    arguments_t arguments;

    if (!parse_args(argc, argv, &arguments)) {
        free_arguments(&arguments);
        return 84;
    }
    free_arguments(&arguments);
    return 0;
}
