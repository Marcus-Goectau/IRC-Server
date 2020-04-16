/*
 * client_handler.h
 * CS3337
 * Written by: Marcus Goeckner
 * 3/10/2020
 *
 * Data structure to handle client data as new clients connect to the server
*/

#include <stdlib.h>
#include <stdio.h>
#include "client_handler.h"
#include <string.h>

/// accepts a new client connection, adds the new client struct to the list of clients
/// \param server_socket: socket fd returned from socket()
/// \param client_address: pointer to a sockaddr struct of the client address
/// \param client_address_length: socklen_t representing the length of the client address
/// \return: a newly created client struct
struct Client* client_handler_getClientConnection(int server_socket, struct sockaddr_in *client_address, int client_address_len) {
    int client_fd = accept(server_socket, (struct sockaddr *) &client_address, &client_address_len);
    char client_name[256];
    struct Client *new_client = (struct Client*)malloc(sizeof(struct Client));
    new_client->client_fd = client_fd; // assigns values to client struct members
    new_client->client_address = (struct sockaddr_in *) client_address;
    new_client->client_length = (socklen_t) client_address_len;
    sprintf(client_name, "Client %d", client_handler_num_connections);
    new_client->nick = malloc(sizeof(client_name));
    new_client->full_name = malloc(sizeof(client_name));
    strcpy(new_client->nick, client_name);
    strcpy(new_client->full_name, client_name);

    return new_client;
}