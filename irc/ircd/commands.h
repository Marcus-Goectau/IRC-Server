/*
 * commands.h
 * CS3337
 * Written by: Marcus Goeckner
 * 4/26/2020
 *
 * Header file for command functionalities
*/

#ifndef IRC_COMMANDS_H
#define IRC_COMMANDS_H

int commands_getCommand(char *command);
int commands_PASS(char *password);
int commands_NICK(char *nic);
int commands_USER(char *user_name, char *server_name, char *real_name);
int commands_OPER(char *user, char *password);
int commands_QUIT(char *message);
int commands_JOIN(char *channel);
int commands_PART(char *channel);
int commands_channel_MODE(char *channel, char mode);
int commands_user_MODE(char *nick_name, char mode);
int commands_TOPIC(char *channel, char *topic);
int commands_NAMES(char *channel);
int commands_LIST();
int commands_INVITE(char *nick_name, char *channel);
int commands_KICK(char *channel, char *user);
int commands_PRIVMSG(char *receiver, char *message);

#endif //IRC_COMMANDS_H
