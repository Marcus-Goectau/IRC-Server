/*
 * commands.c
 * CS3337
 * Written by: Marcus Goeckner
 * 4/26/2020
 *
 * support for command messages sent by clients
*/

#include "commands.h"

int commands_getCommand(char *command) {
    return 1;
}

int commands_PASS(char *password) {
    return 1;
}

int commands_NICK(char *nic) {
    return 1;
}

int commands_USER(char *user_name, char *server_name, char *real_name) {
    return 1;
}

int commands_OPER(char *user, char *password) {
    return 1;
}

int commands_QUIT(char *message) {
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
