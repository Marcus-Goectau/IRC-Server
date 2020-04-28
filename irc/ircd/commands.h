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

int commands_getCommand(char *command, struct Client *client);
void commands_checkCommandStatus(int command_status, struct Client *client);
int commands_PASS(char *password);
int commands_NICK(char *nick, struct Client *client);
int commands_USER(char *full_name, struct Client *client);
int commands_OPER(char *user, struct Client *client);
int commands_QUIT(char *message, struct Client *client);
int commands_JOIN(char *channel, struct Client *client);
int commands_PART(char *channel, struct Client *part);
int commands_channel_MODE(char *channel, char mode);
int commands_user_MODE(char *nick_name, char mode);
int commands_TOPIC(char *channel, char *topic, struct Client *client);
int commands_NAMES(char *channel);
int commands_LIST();
int commands_INVITE(char *nick_name, char *channel);
int commands_KICK(char *channel, char *user);
int commands_PRIVMSG(char *receiver, char *message);

#endif //IRC_COMMANDS_H
