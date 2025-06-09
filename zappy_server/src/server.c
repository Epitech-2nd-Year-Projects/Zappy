/*
** EPITECH PROJECT, 2025
** zappy_server
** File description:
** server
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
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

static int set_nonblocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);

    if (flags == ERROR) {
        return ERROR;
    }
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0) {
        perror("fcntl");
        return ERROR;
    }
    return EXIT_SUCCESS;
}

static int create_listener_socket(const arguments_t *args, int max_clients)
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
        || listen(fd, max_clients) < 0) {
        return close(fd), ERROR;
    }
    return fd;
}

static void remove_client(server_t *server, int index)
{
    if (server->clients[index].team_name != NULL) {
        free(server->clients[index].team_name);
    }
    close(server->clients[index].fd);
    server->clients[index] = server->clients[server->clients_count - 1];
    server->pfds[index + 1] = server->pfds[server->clients_count];
    server->clients_count--;
}

static void accept_clients(server_t *s, time_t now)
{
    for (int fd = accept(s->listen_fd, NULL, NULL); fd >= 0;
        fd = accept(s->listen_fd, NULL, NULL)) {
        if (set_nonblocking(fd) < 0) {
            close(fd);
            continue;
        }
        if (s->clients_count >= s->max_clients) {
            close(fd);
            continue;
        }
        s->clients[s->clients_count] = (client_t){fd, now,
            CLIENT_TYPE_UNKNOWN, NULL, {0}, 0};
        memset(s->clients[s->clients_count].input_buffer, 0, BUFFER_SIZE);
        s->pfds[s->clients_count + 1].fd = fd;
        s->pfds[s->clients_count + 1].events = POLLIN;
        s->clients_count++;
    }
    if (errno != EAGAIN && errno != EWOULDBLOCK)
        perror("accept");
}

static bool process_client(server_t *server, int index, time_t now)
{
    struct pollfd *pfd = &server->pfds[index + 1];
    client_t *client = &server->clients[index];
    char buffer[BUFFER_SIZE] = {0};

    if (pfd->revents & (POLLERR | POLLHUP)) {
        return false;
    }
    if (pfd->revents & POLLIN) {
        if (recv(client->fd, buffer, sizeof(buffer), 0) <= 0) {
            return false;
        }
        client->last_active = now;
    }
    if (difftime(now, client->last_active) > IDLE_TIMEOUT) {
        return false;
    }
    return true;
}

static void handle_clients(server_t *server, time_t now)
{
    int i = 0;

    while (i < server->clients_count) {
        if (!process_client(server, i, now)) {
            remove_client(server, i);
            continue;
        }
        i++;
    }
}

static int setup_server(const arguments_t *args, server_t *server)
{
    server->max_clients = args->clients > 0 ? args->clients : 10;
    server->listen_fd = create_listener_socket(args, server->max_clients);
    server->clients_count = 0;
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
    for (int i = 0; i < server->clients_count; i++) {
        if (server->clients[i].team_name != NULL) {
            free(server->clients[i].team_name);
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
