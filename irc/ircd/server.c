/*
 * server.c
 * CS3337
 * Written by: Marcus Goeckner
 * Professor McGregor
 * 2/21/2020
 *
 * Creates a TCP server socket that binds to an IP address and port 
 * to listen for connections
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>
#include "linked_list.h"
#include "client_handler.h"
#include "logger.h"
#include "channel.h"

void *communicate(void *);

void error(char *message) {
    fprintf(stderr, message);
    logger_write(message);
    exit(1);
}

int main(int argc, char *argv[]) {
	// output error message if no port argument is provided 
	if (argc < 2) {
		error("ERROR: no port provided");
	}

	client_handler_max_connections = 10;
	logger_logging_level = 1;
	sprintf(logger_log_file_location, "\\logs\\server.log");

	int port_num = atoi(argv[1]);

	// create a new stream (TCP) socket
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0) {
		error("ERROR: could not create server socket");
	}

	// allow immediate reuse of this address
	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
	    error("ERROR: setsockopt(SO_REUSEADDR) failed");

	// define server address and declare a client address to be used 
	// when accepting connections
	struct sockaddr_in server_address, client_address;
	bzero((char *) &server_address, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port_num);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// bind the socket to the specified IP address and port
	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	
	// listen for connections
	listen(server_socket, client_handler_max_connections);
	int client_len = sizeof(client_address);
	// loop to continuously accept connections
	while(client_handler_num_connections <= client_handler_max_connections) {
		// accept connections on the server socket and create new threads 
		// to deal with clients
		struct Client *new_client = client_handler_getClientConnection(server_socket, (struct sockaddr *) &client_address, &client_len);

		// Add new client to running list of clients
		if (linked_list_size(client_list_head) == 0) {
            client_list_head = (struct LinkedListNode*) malloc(sizeof(struct LinkedListNode));
            client_list_head->data = new_client;
            new_client->is_op = 1;
            new_client->nick = "Client 0";
            new_client->full_name = "Client 0";
		} else {
            linked_list_push((struct LinkedListNode**)client_list_head, new_client);
		}

        client_handler_num_connections = linked_list_size(client_list_head);

		if (new_client->client_fd < 0) {
			error("ERROR: could not accept new connection\n");
		}
		char new_client_info[256];
		sprintf(new_client_info, "New client name: %s\nNew client fd: %d\nNew client op status: %d\nConnected clients: %d\n",
		        new_client->nick, new_client->client_fd, new_client->is_op, client_handler_num_connections);
		printf("%s\n", new_client_info);
		logger_write(new_client_info);
		pthread_t thread;
		pthread_create(&thread, NULL, communicate, (void *)new_client->client_fd); // spin off new thread for client
	}
	return 0;
}

// function to communicate with each client in their own thread
void* communicate(void* arg) {
	char buffer[256];
	int conn_status = 0;
	int new_client_socket = (int)arg;
	char sender[256];
	while(conn_status >= 0) {
		bzero(buffer, 256);
		bzero(sender, 256);
		strcpy(sender, "Message From ");
		conn_status = read(new_client_socket, buffer, 255);
		if (conn_status < 0) {
			error("ERROR: could not read from socket");
		}
		printf("Message from FD %d: %s\n", new_client_socket, buffer);
		struct LinkedListNode *node = client_list_head;
        struct Client *client;
        while(node != NULL) {
            client = node->data;
            if (client->client_fd == new_client_socket) {
                sprintf(sender, client->nick);
            }
            node = node->next;
        }
        node = client_list_head;
        // Loop through list of clients and broadcast received messages to all other clients
        while(node != NULL) {
		    client = node->data;
		    if (client->client_fd != new_client_socket) {
		        conn_status = write(client->client_fd, &sender, 255);
                conn_status = write(client->client_fd, &buffer, 255);
		    }
            if (conn_status < 0) {
                error("ERROR: could not  write to socket");
            }
            node = node->next;
		}
		free(node);
	}
	close(new_client_socket);
	return 0;
}
