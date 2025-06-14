/*
** EPITECH PROJECT, 2025
** zappy_server
** File description:
** server
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <poll.h>
#include <time.h>

#include "arguments.h"
#include "server.h"
#include "constants.h"
#include "message_queue.h"
#include "client.h"

static int create_listener_socket(const arguments_t *args)
{
    struct sockaddr_in addr = {0};
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd < 0) {
        return ERROR;
    }
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    if (set_nonblocking(fd) < 0) {
        return close(fd), ERROR;
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(args->port);
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0
        || listen(fd, SOMAXCONN) < 0) {
        return close(fd), ERROR;
    }
    return fd;
}

static int setup_server(const arguments_t *args, server_t *server)
{
    int max_ai = args->team_count * args->clients;

    server->max_clients = max_ai + 1;
    server->listen_fd = create_listener_socket(args);
    server->clients_count = 0;
    server->arguments = args;
    if (server->listen_fd < 0) {
        return ERROR;
    }
    server->pfds = calloc(server->max_clients + 1, sizeof(struct pollfd));
    server->clients = calloc(server->max_clients, sizeof(client_t));
    if (server->pfds == NULL || server->clients == NULL) {
        perror("calloc");
        free(server->pfds);
        free(server->clients);
        close(server->listen_fd);
        return ERROR;
    }
    return EXIT_SUCCESS;
}

static bool server_loop(server_t *server)
{
    int return_value = poll(server->pfds, server->clients_count + 1, 1000);
    time_t now = time(NULL);

    if (return_value < 0) {
        if (errno == EINTR) {
            return true;
        }
        perror("poll");
        return false;
    }
    if (server->pfds[0].revents & POLLIN) {
        accept_clients(server, now);
    }
    handle_clients(server, now);
    return true;
}

static void cleanup_server(server_t *server)
{
    message_t *tmp = NULL;

    for (int i = 0; i < server->clients_count; i++) {
        if (server->clients[i].team_name != NULL) {
            free(server->clients[i].team_name);
        }
        while (server->clients[i].out_head != NULL) {
            tmp = server->clients[i].out_head;
            server->clients[i].out_head = tmp->next;
            free(tmp->data);
            free(tmp);
        }
        close(server->clients[i].fd);
    }
    free(server->clients);
    free(server->pfds);
    close(server->listen_fd);
}

int run_server(const arguments_t *args)
{
    server_t server = {0};

    if (setup_server(args, &server) < 0) {
        return ERROR;
    }
    server.pfds[0].fd = server.listen_fd;
    server.pfds[0].events = POLLIN;
    while (server_loop(&server))
        ;
    cleanup_server(&server);
    return EXIT_SUCCESS;
}
