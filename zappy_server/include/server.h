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

typedef struct client_s {
    int fd;
    time_t last_active;
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
