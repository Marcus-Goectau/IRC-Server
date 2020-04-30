/*
 * commands.c
 * CS3337
 * Written by: Marcus Goeckner
 * 4/26/2020
 *
 * support for interpreting command messages sent by clients
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
#include <pthread.h>

/// parses command from messages sent from clients and calls appropriate function
/// \param command: command and arguments to be parsed
/// \param client: client who sent the command
/// \return: exit code depending on the command being called
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
            write(client->client_fd, "You need to have op status to raise the op status of another user.\n", 70);
        } else if (command_status == -3) {
            sprintf(buffer,
                    "ERROR: %s tried to raise the op status of another client, but a client with the input nick name does not exist.\n",
                    client->nick);
            logger_write(buffer);
            printf(buffer);
            write(client->client_fd, "There is no user with that nick name.\n", 40);
        } else if (command_status == -4) {
            sprintf(buffer,
                   "ERROR: %s tried to create a channel, but the channel name did not start with \'#\'.\n",
                   client->nick);
            logger_write(buffer);
            printf(buffer);
            write(client->client_fd, "Channel names must start with \'#\' and contain no spaces.\n", 70);
        } else if (command_status == -5) {
            sprintf(buffer,
                    "ERROR: %s tried to join a channel that they are already in.\n",
                    client->nick);
            logger_write(buffer);
            printf(buffer);
            write(client->client_fd, "You cannot join a channel you are already in.\n", 50);
        } else if (command_status = -6) {
            sprintf(buffer,
                    "ERROR: %s tried to join a channel, but are they already in a channel.\n",
                    client->nick);
            logger_write(buffer);
            printf(buffer);
            write(client->client_fd, "You must leave your current channel before joining another one. (use /part)\n", 100);
        }
    }
}

/// changes the nick name of the client who calls this command
/// \param nick: new nick name of this client
/// \param client: the client whos nick name is being changed
/// \return: exit code
int commands_NICK(char *nick, struct Client *client) {
    nick[strlen(nick) - 1] = '\0';
    client->nick = malloc(strlen(nick) + 1);
    strcpy(client->nick, nick);
    return 0;
}

/// changes the full name of the client who calls this command
/// \param full_name: new full name of this client
/// \param client: the client whos full name is being changed
/// \return: exit code
int commands_USER(char *full_name, struct Client *client) {
    full_name[strlen(full_name) - 1] = '\0';
    client->nick = malloc(strlen(full_name) + 1);
    strcpy(client->full_name, full_name);
    return 0;
}

/// elevates the op status of another user if the client calling this command has op status
/// \param user: the nick name of the user to raise the op status of
/// \param client: the client performing the op status change
/// \return: exit code
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

/// allows a client to quit the server
/// \param message: quit message
/// \param client: the client quiting the server
/// \return: exit code
int commands_QUIT(char *message, struct Client *client) {
    char quit_message[256];
    shutdown(client->client_fd, 2);
    close(client->client_fd);
    struct LinkedListNode *node = linked_list_get(client_list_head, client);
    linked_list_delete(&client_list_head, node);    // remove client from list of clients
    client_handler_num_connections = linked_list_size(client_list_head);

    sprintf(quit_message, "%s has left: %s\n\n", client->nick, message);
    struct LinkedListNode *current_node = client_list_head;
    struct Client *current_client;

    int conn_status = 0;
    while (current_node != NULL) {
        current_client = current_node->data;
        conn_status = write(current_client->client_fd, quit_message, 256); // write disconnect message to clients
        if (conn_status < 0) {
            fprintf(stderr, "ERROR: could not write to socket");
            logger_write("ERROR: could not write to socket");
            exit(1);
        }
        current_node = current_node->next;
    }

    printf("%s", quit_message);
    logger_write(quit_message);
    pthread_exit(0);
}

/// joins a channel on the server by name (a new channel is created if no channel with the requested name is found)
/// \param channel: name of the channel to join
/// \param client: the client trying to join a channel
/// \return: exit code
int commands_JOIN(char *channel, struct Client *client) {

    channel[strlen(channel) - 1] = '\0';
    if (strncmp(channel, "#", 1) != 0) {
        return -4;
    }

    if (client->in_channel == 1) {
        return -6;
    }

    if (channel_list_head == NULL) {
        struct Channel *new_channel = channel_create(channel, "Topic"); // create a new channel if no channels are present
        linked_list_push(&channel_list_head, new_channel);
        linked_list_push(&new_channel->subscriber_list_head, client);
        channel_num_channels = linked_list_size(channel_list_head);
        client->in_channel = 1;
        char channel_message[256];
        sprintf(channel_message, "You have created and joined the channel: %s\n", channel);
        write(client->client_fd, channel_message, 256);
        char log_message[256];
        sprintf(log_message, "%s has created a channel: %s\n\n", client->nick, channel);
        fprintf(stdout,"%s", log_message);
        logger_write(log_message);
        return 0;
    } else {
        struct LinkedListNode *node = channel_list_head;
        struct Channel *current_channel = node->data;
        while (node != NULL && strcmp(current_channel->name, channel) != 0) {   // find the channel to join
            node = node->next;
            current_channel = node->data;
        }
        if (node == NULL) { // channel doesnt exist yet
            struct Channel *new_channel = channel_create(channel, "Topic"); // create a new channel if no channel with requested name is present
            linked_list_push(&channel_list_head, new_channel);
            linked_list_push(&new_channel->subscriber_list_head, client);
            channel_num_channels = linked_list_size(channel_list_head);
            client->in_channel = 1;
            char channel_message[256];
            sprintf(channel_message, "You have created and joined the channel: %s", channel);
            char log_message[256];
            sprintf(log_message, "%s has created a channel: %s", client->nick, channel);
            printf("%s", log_message);
            logger_write(log_message);
            write(client->client_fd, channel_message, 256);
        } else {
            struct LinkedListNode *current_node = current_channel->subscriber_list_head;
            struct Client *current_client;
            while (current_node != NULL) {
                current_client = current_node->data;
                if (strcmp(current_client->nick, client->nick) == 0) {  // check if this client is already in this channel
                    return -5;
                }
                current_node = current_node->next;
            }
            linked_list_push(&current_channel->subscriber_list_head, client);
            char channel_message[256];
            char user[256];
            sprintf(channel_message, "You have joined the channel: %s TOPIC: %s\nUsers in this channel:\n", channel, current_channel->topic);
            client->in_channel = 1;
            write(client->client_fd, channel_message, 256);
            struct LinkedListNode *node = current_channel->subscriber_list_head;
            while (node != NULL) {
                usleep(1000);
                current_client = node->data;
                bzero(user, 256);
                sprintf(user, "%s", current_client->nick);
                write(client->client_fd, user, 256);
                node = node->next;
            }
        }
    }

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

int commands_NAMES(char *channel, struct Client *client) {
    return 0;
}

int commands_LIST(struct Client *client) {
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
