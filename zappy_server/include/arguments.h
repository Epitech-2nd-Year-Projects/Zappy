/*
** EPITECH PROJECT, 2025
** zappy_server [WSL: Ubuntu]
** File description:
** arguments
*/

#ifndef ARGUMENTS_H_

    #define ARGUMENTS_H_
    #include <stddef.h>
    #include <stdbool.h>

typedef struct arguments_s {
    int port;
    int width;
    int height;
    int team_count;
    char **team_names;
    int clients;
    int freq;
} arguments_t;

typedef struct argument_handler_s {
    const char *argument_name;
    int (*handler)(int argc, char **argv, arguments_t *arguments, int index);
} argument_handler_t;

int help_handler(int argc, char **argv, arguments_t *arguments,
    int index);
int port_handler(int argc, char **argv, arguments_t *arguments,
    int index);
int width_handler(int argc, char **argv, arguments_t *arguments,
    int index);
int height_handler(int argc, char **argv, arguments_t *arguments,
    int index);
int teams_handler(int argc, char **argv, arguments_t *arguments,
    int index);
int clients_handler(int argc, char **argv, arguments_t *arguments,
    int index);
int freq_handler(int argc, char **argv, arguments_t *arguments,
    int index);

static const argument_handler_t HANDLERS[] = {
    { "-h", help_handler },
    { "-p", port_handler },
    { "-x", width_handler },
    { "-y", height_handler },
    { "-n", teams_handler },
    { "-c", clients_handler },
    { "-f", freq_handler },
    { NULL, NULL }
};

void print_usage(const char *prog_name);
bool parse_args(int argc, char *argv[], arguments_t *arguments);
void free_arguments(arguments_t *arguments);

#endif /* !ARGUMENTS_H_ */
