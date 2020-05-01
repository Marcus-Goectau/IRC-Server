/*
 * channel.c
 * CS3337
 * Written by: Marcus Goeckner
 * 3/12/2020
 *
 * Data structure to handle channels and their components
*/

#include <stdlib.h>
#include <string.h>
#include "channel.h"

/// create a new channel
/// \param name: name of the channel
/// \param topic: topic of the channel
/// \return: a newly created
struct Channel* channel_create(const char *name, const char *topic) {
    struct Channel *new_channel = (struct Channel*) malloc(sizeof(struct Channel));

    new_channel->name = malloc(sizeof(name));
    strcpy(new_channel->name, name);
    new_channel->topic = malloc(sizeof(topic));
    strcpy(new_channel->topic, topic);

    return new_channel;
}

/// searches for a channel in the list of channels by name
/// \param name: name of the target channel to find
/// \return: channel with specified name
struct Channel* channel_findChannel(char *name, struct LinkedListNode *head) {
    struct LinkedListNode *node = head;
    struct Channel *channel = node->data;
    while (node != NULL && strcmp(channel->name, name) != 0) {
        node = node->next;
        if (node != NULL) {
            channel= node->data;
        } else {
            channel= NULL;
        }

    }
    return channel;
}

