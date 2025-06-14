/*
** EPITECH PROJECT, 2025
** zappy_server
** File description:
** client
*/

#ifndef CLIENT_H
    #define CLIENT_H

    #include <time.h>

    #include "server.h"

void handle_clients(server_t *server, time_t now);
void accept_clients(server_t *s, time_t now);
int set_nonblocking(int fd);

#endif
