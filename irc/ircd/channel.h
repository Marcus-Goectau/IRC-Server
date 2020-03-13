/*
 * channel.h
 * CS3337
 * Written by: Marcus Goeckner
 * 3/12/2020
 *
 * Header file for channel handling data structure
*/
#ifndef IRC_CHANNEL_H
#define IRC_CHANNEL_H

#include <sys/socket.h>
#include <sys/types.h>
#include "client_handler.h"
#include "linked_list.h"

struct Channel {
    struct LinkedListNode *client_list_head; // List of users in this channel
    char *name;
    char *topic;
    pthread_mutex_t channel_mutex; //To avoid two threads editing client_list at the same time
};

struct Channel* channel_create(char *name, char *topic);

struct LinkedListNode *channel_list_head;

#endif //IRC_CHANNEL_H
