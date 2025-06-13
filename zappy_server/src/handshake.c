/*
** EPITECH PROJECT, 2025
** zappy_server
** File description:
** handshake
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arguments.h"
#include "server.h"

static bool is_valid_team(const arguments_t *args, const char *name)
{
    for (int i = 0; i < args->team_count; i++) {
        if (strcmp(args->team_names[i], name) == 0) {
            return true;
        }
    }
    return false;
}

static int team_free_slots(const server_t *server, const char *team)
{
    int count = 0;

    for (int i = 0; i < server->clients_count; i++) {
        if (server->clients[i].team_name != NULL
            && strcmp(server->clients[i].team_name, team) == 0
            && server->clients[i].type & CLIENT_TYPE_AI) {
            count++;
        }
    }
    return server->arguments->clients - count;
}

static bool assign_team(server_t *server, client_t *client, const char *name)
{
    char *msg = NULL;
    int slots = 0;

    if (!is_valid_team(server->arguments, name))
        return false;
    slots = team_free_slots(server, name);
    if (slots <= 0)
        return false;
    client->team_name = strdup(name);
    if (client->team_name == NULL) {
        perror("strdup");
        return false;
    }
    client->type = CLIENT_TYPE_AI;
    if (asprintf(&msg, "%d\n %d %d\n",
        slots - 1, server->arguments->width, server->arguments->height) < 0) {
        return false;
    }
    queue_push(client, msg);
    free(msg);
    return true;
}

static bool handle_handshake_line(server_t *server, client_t *client, char *line)
{
    if (strncmp(line, "TEAM ", 5) == 0) {
        return assign_team(server, client, line + 5);
    }
    if (strcmp(line, "GRAPHIC") == 0) {
        client->type = CLIENT_TYPE_GUI;
        return true;
    }
    return false;
}

bool handshake_process(server_t *server, client_t *client)
{
    char *nl = memchr(client->input_buffer, '\n', client->buffer_pos);

    while (nl != NULL) {
        char line[BUFFER_SIZE];
        size_t len = (size_t)(nl - client->input_buffer);

        memcpy(line, client->input_buffer, len);
        line[len] = '\0';
        memmove(client->input_buffer, nl + 1, client->buffer_pos - len - 1);
        client->buffer_pos -= len + 1;
        if (!handle_handshake_line(server, client, line))
            return false;
        nl = memchr(client->input_buffer, '\n', client->buffer_pos);
    }
    return true;
}