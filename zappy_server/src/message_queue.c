/*
** EPITECH PROJECT, 2025
** zappy_server
** File description:
** message_queue
*/

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "server.h"

bool queue_push(client_t *client, const char *msg)
{
    message_t *node = malloc(sizeof(message_t));

    if (node == NULL) {
        return false;
    }
    node->data = strdup(msg);
    if (node->data == NULL) {
        return free(node), false;
    }
    node->len = strlen(msg);
    node->sent = 0;
    node->next = NULL;
    if (client->out_tail != NULL) {
        client->out_tail->next = node;
    } else {
        client->out_head = node;
    }
    client->out_tail = node;
    return true;
}

bool queue_send(client_t *client)
{
    message_t *msg = NULL;
    ssize_t w = 0;

    while (client->out_head != NULL) {
        msg = client->out_head;
        w = send(client->fd, msg->data + msg->sent, msg->len - msg->sent, 0);
        if (w < 0)
            return false;
        msg->sent += w;
        if (msg->sent < msg->len)
            break;
        client->out_head = msg->next;
        if (client->out_head == NULL)
            client->out_tail = NULL;
        free(msg->data);
        free(msg);
    }
    return true;
}
