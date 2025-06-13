/*
** EPITECH PROJECT, 2025
** zappy_server
** File description:
** message_queue
*/

#ifndef MESSAGE_QUEUE_H
    #define MESSAGE_QUEUE_H

typedef struct client_s client_t;

typedef struct message_s {
    char *data;
    size_t len;
    size_t sent;
    struct message_s *next;
} message_t;

bool queue_push(client_t *client, const char *msg);
bool queue_send(client_t *client);

#endif
