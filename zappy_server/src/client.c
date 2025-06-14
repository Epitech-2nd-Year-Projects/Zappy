/*
** EPITECH PROJECT, 2025
** zappy_server
** File description:
** client
*/

#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>

#include "server.h"
#include "arguments.h"
#include "handshake.h"
#include "message_queue.h"
#include "constants.h"

static void remove_client(server_t *sv, int idx)
{
    message_t *msg = NULL;

    free(sv->clients[idx].team_name);
    while (sv->clients[idx].out_head) {
        msg = sv->clients[idx].out_head;
        sv->clients[idx].out_head = msg->next;
        free(msg->data);
        free(msg);
    }
    close(sv->clients[idx].fd);
    sv->clients_count--;
    if (idx < sv->clients_count) {
        sv->clients[idx] = sv->clients[sv->clients_count];
        sv->pfds[idx + 1] = sv->pfds[sv->clients_count + 1];
    }
    memset(&sv->clients[sv->clients_count], 0, sizeof(client_t));
}

static int count_ai(const server_t *sv)
{
    int c = 0;

    for (int i = 0; i < sv->clients_count; i++) {
        if (sv->clients[i].type == CLIENT_TYPE_AI)
            c++;
    }
    return c;
}

static bool can_accept(const server_t *sv)
{
    int max_ai = sv->arguments->team_count * sv->arguments->clients;

    if (sv->clients_count >= sv->max_clients)
        return false;
    return count_ai(sv) < max_ai;
}

int set_nonblocking(int fd)
{
    int flags = fcntl(fd, F_GETFL);

    if (flags == ERROR)
        return ERROR;
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0) {
        perror("fcntl");
        return ERROR;
    }
    return EXIT_SUCCESS;
}

static void init_client(server_t *sv, int fd, time_t now)
{
    client_t *cl = &sv->clients[sv->clients_count];

    *cl = (client_t){fd, now, CLIENT_TYPE_UNKNOWN, NULL, {0}, 0, NULL, NULL};
    memset(cl->input_buffer, 0, BUFFER_SIZE);
    sv->pfds[sv->clients_count + 1].fd = fd;
    sv->pfds[sv->clients_count + 1].events = POLLIN | POLLOUT;
    queue_push(cl, "WELCOME\n");
    sv->clients_count++;
}

void accept_clients(server_t *sv, time_t now)
{
    for (int fd = accept(sv->listen_fd, NULL, NULL); fd >= 0;
        fd = accept(sv->listen_fd, NULL, NULL)) {
        if (set_nonblocking(fd) < 0 || !can_accept(sv)) {
            close(fd);
            continue;
        }
        init_client(sv, fd, now);
    }
    if (errno != EAGAIN && errno != EWOULDBLOCK)
        perror("accept");
}

static bool handle_read(server_t *sv, client_t *cl, time_t now)
{
    char buf[BUFFER_SIZE] = {0};
    ssize_t r = recv(cl->fd, buf, sizeof(buf), 0);

    if (r <= 0 || cl->buffer_pos + (size_t)r >= BUFFER_SIZE)
        return false;
    memcpy(cl->input_buffer + cl->buffer_pos, buf, (size_t)r);
    cl->buffer_pos += (size_t)r;
    if (cl->type == CLIENT_TYPE_UNKNOWN) {
        if (!handshake_process(sv, cl))
            return false;
    }
    cl->last_active = now;
    return true;
}

static bool process_client(server_t *sv, int idx, time_t now)
{
    struct pollfd *p = &sv->pfds[idx + 1];
    client_t *cl = &sv->clients[idx];

    if (p->revents & (POLLERR | POLLHUP))
        return false;
    if (p->revents & POLLIN && !handle_read(sv, cl, now))
        return false;
    if (p->revents & POLLOUT && !queue_send(cl))
        return false;
    p->events = POLLIN | (cl->out_head ? POLLOUT : 0);
    if (difftime(now, cl->last_active) > IDLE_TIMEOUT)
        return false;
    return true;
}

void handle_clients(server_t *sv, time_t now)
{
    int i = 0;

    while (i < sv->clients_count) {
        if (!process_client(sv, i, now)) {
            remove_client(sv, i);
        } else {
            i++;
        }
    }
}
