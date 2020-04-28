/*
 * commands.c
 * CS3337
 * Written by: Marcus Goeckner
 * 4/26/2020
 *
 * support for command messages sent by clients
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "client_handler.h"
#include "channel.h"
#include "commands.h"
#include "linked_list.h"

/// parses command from messages sent from clients and calls appropriate function
/// \param command: command and arguments to be parsed
/// \param client: client who sent the command
/// \return: -1 on fail to get command and 0 if successful
int commands_getCommand(char *command, struct Client *client) {

    char arguments[100];

    if (command == NULL) {
        return -1;
    }

    if (strncmp(command, "nick", 4) == 0) {
        strcpy(arguments, command + 5);
        return commands_NICK(arguments, client);
    }else if (strncmp(command, "user", 4) == 0) {
        strcpy(arguments, command + 5);
        return commands_USER(arguments, client);
    } else if (strncmp(command, "oper", 4) == 0) {
        strcpy(arguments, command + 5);
        return commands_OPER(arguments, client);
    } else if (strncmp(command, "quit", 4) == 0) {
        strcpy(arguments, command + 5);
        return commands_QUIT(arguments, client);
    } else {
        return -1;
    }
}

int commands_NICK(char *nick, struct Client *client) {
    nick[strlen(nick) - 1] = '\0';
    client->nick = malloc(strlen(nick) + 1);
    strcpy(client->nick, nick);
    return 0;
}

int commands_USER(char *full_name, struct Client *client) {
    return 1;
}

int commands_OPER(char *user, struct Client *client) {
    return 1;
}

int commands_QUIT(char *message, struct Client *client) {
    return 1;
}

int commands_JOIN(char *channel) {
    return 1;
}

int commands_PART(char *channel) {
    return 1;
}

int commands_channel_MODE(char *channel, char mode) {
    return 1;
}

int commands_user_MODE(char *nick_name, char mode) {
    return 1;
}

int commands_TOPIC(char *channel, char *topic) {
    return 1;
}

int commands_NAMES(char *channel) {
    return 1;
}

int commands_LIST() {
    return 1;
}

int commands_INVITE(char *nick_name, char *channel) {
    return 1;
}

int commands_KICK(char *channel, char *user) {
    return 1;
}

int commands_PRIVMSG(char *receiver, char *message) {
    return 1;
}
