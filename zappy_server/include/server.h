/*
** EPITECH PROJECT, 2025
** zappy_server
** File description:
** server
*/

#ifndef SERVER_H
    #define SERVER_H

    #include <time.h>

    #define IDLE_TIMEOUT 30

    #define BUFFER_SIZE 1024

typedef enum client_type_e {
    CLIENT_TYPE_UNKNOWN = 0,
    CLIENT_TYPE_AI,
    CLIENT_TYPE_GUI
} client_type_t;

typedef struct client_s {
    int fd;
    time_t last_active;
    client_type_t type;
    char *team_name;
    char input_buffer[BUFFER_SIZE];
    size_t buffer_pos;
} client_t;

typedef struct server_s {
    int listen_fd;
    int max_clients;
    int clients_count;
    struct pollfd *pfds;
    struct client_s *clients;
} server_t;

int run_server(const arguments_t *arguments);

#endif
