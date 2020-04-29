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
#include <unistd.h>
#include <string.h>
#include "client_handler.h"
#include "channel.h"
#include "commands.h"
#include "logger.h"
#include "linked_list.h"

/// parses command from messages sent from clients and calls appropriate function
/// \param command: command and arguments to be parsed
/// \param client: client who sent the command
/// \return: -1 on fail to get command and 0 if successful
int commands_getCommand(char *command, struct Client *client) {

    char arguments[100];

    if (command == NULL || client == NULL) {
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
    } else if (strncmp(command, "join", 4) == 0) {
        strcpy(arguments, command + 5);
        return commands_JOIN(arguments, client);
    } else if (strncmp(command, "part", 4) == 0) {
        strcpy(arguments, command + 5);
        return commands_PART(arguments, client);
    } else if (strncmp(command, "topic", 5) == 0) {
        strcpy(arguments, command + 6);
        return commands_TOPIC(arguments, arguments, client); // need to figure out how to split arguments into two strings
    }else {
        return -1;
    }
}

/// Checks return values from commmands functions and displays error messages to clients
/// \param command_status: return value from attempted command sent from client
/// \param client: client who sent the command
void commands_checkCommandStatus(int command_status, struct Client *client) {
    char buffer[256];
    if (command_status != 0) {
        if (command_status == -1) {
            sprintf(buffer, "ERROR: could not parse command from %s\n", client->nick);
            logger_write(buffer);
            printf(buffer);
            write(client->client_fd, "Invalid command format. Use /help for command help.\n", 50);
        } else if (command_status == -2) {
            sprintf(buffer,
                    "ERROR: %s tried to raise the op status of another client, but does not have privileges to do so.\n",
                    client->nick);
            logger_write(buffer);
            printf(buffer);
            write(client->client_fd, "You need to have op status to raise the op status of another user.\n", 100);
        } else if (command_status == -3) {
            sprintf(buffer,
                    "ERROR: %s tried to raise the op status of another client, but a client with that nick name does not exist.\n",
                    client->nick);
            logger_write(buffer);
            printf(buffer);
            write(client->client_fd, "There is no user with that nick name.\n", 50);
        }
    }
}

int commands_NICK(char *nick, struct Client *client) {
    nick[strlen(nick) - 1] = '\0';
    client->nick = malloc(strlen(nick) + 1);
    strcpy(client->nick, nick);
    return 0;
}

int commands_USER(char *full_name, struct Client *client) {
    full_name[strlen(full_name) - 1] = '\0';
    client->nick = malloc(strlen(full_name) + 1);
    strcpy(client->full_name, full_name);
    return 0;
}

int commands_OPER(char *user, struct Client *client) {
    if (client->is_op != 1) {
        return -2;
    }
    struct Client *target_client = client_handler_findClient(user, client_list_head);
    if (target_client != NULL) {
        target_client->is_op = 1;
        return 0;
    }
    return -3;
}

int commands_QUIT(char *message, struct Client *client) {
    return 0;
}

int commands_JOIN(char *channel, struct Client *client) {
    return 0;
}

int commands_PART(char *channel, struct Client *client) {
    return 0;
}

int commands_channel_MODE(char *channel, char mode) {
    return 0;
}

int commands_user_MODE(char *nick_name, char mode) {
    return 0;
}

int commands_TOPIC(char *channel, char *topic, struct Client *client) {
    return 0;
}

int commands_NAMES(char *channel) {
    return 0;
}

int commands_LIST() {
    return 0;
}

int commands_INVITE(char *nick_name, char *channel) {
    return 0;
}

int commands_KICK(char *channel, char *user) {
    return 0;
}

int commands_PRIVMSG(char *receiver, char *message) {
    return 0;
}
