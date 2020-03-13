/*
 * client_handler.h
 * CS3337
 * Written by: Marcus Goeckner
 * 3/10/2020
 *
 * Data structure to handle client data as new clients connect to the server
*/

#include <stdlib.h>
#include "client_handler.h"

/// accepts a new client connection, adds the new client struct to the list of clients
/// \param server_socket: socket fd returned from socket()
/// \param client_address: pointer to a sockaddr struct of the client address
/// \param client_address_length: socklen_t representing the length of the client address
/// \return: a newly created client struct
struct Client* client_handler_getClientConnection(int server_socket, struct sockaddr_in *client_address, int client_address_len, char *nick_name, char *full_name) {
    int client_fd = accept(server_socket, (struct sockaddr *) &client_address, &client_address_len);

    struct Client *new_client = (struct Client*)malloc(sizeof(struct Client));
    new_client->client_fd = client_fd; // assigns values to client struct members
    new_client->client_address = (struct sockaddr_in *) client_address;
    new_client->client_length = (socklen_t) client_address_len;
    new_client->nick = nick_name;
    new_client->full_name = full_name;
    if (linked_list_size(client_list_head) == 0) {
        new_client ->is_op = 1;
    }


    return new_client;


}