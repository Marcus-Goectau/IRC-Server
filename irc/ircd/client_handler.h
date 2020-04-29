/*
 * client_handler.h
 * CS3337
 * Written by: Marcus Goeckner
 * 3/10/2020
 *
 * Header file for client handling data structure
*/

#ifndef IRCD_CLIENT_HANDLER_H
#define IRCD_CLIENT_HANDLER_H

#include <netinet/in.h>
#include <sys/socket.h>
#include "linked_list.h"

struct Client {
    int client_fd;
    struct hostent *server;
    struct sockaddr_in *client_address;
    socklen_t client_length;
    int is_op; // boolean
    char *nick;
    char *full_name;
    int processing; // boolean
};

struct Client* client_handler_getClientConnection(int server_socket, struct sockaddr_in *client_address, int client_address_len);
struct Client* client_handler_findClient(char* nick_name, struct LinkedListNode *head);

struct LinkedListNode *client_list_head; // List to hold all of the clients
int client_handler_num_connections;
int client_handler_num_processing;
int client_handler_max_connections;
pthread_mutex_t client_handler_connections_mutex;
int client_handler_buffer_size;

#endif //IRCD_CLIENT_HANDLER_H
