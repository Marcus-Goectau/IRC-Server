/*
 * channel.c
 * CS3337
 * Written by: Marcus Goeckner
 * 3/12/2020
 *
 * Data structure to handle channels and their components
*/

# include <stdlib.h>
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

