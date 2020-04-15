/*
 * client.c 
 * CS3337
 * Written by: Marcus Goeckner
 * Professor McGregor
 * 2/21/2020
 * 
 * Creates a TCP  client socket to send and recieve data from another socket endpoint i.e. a server
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include "client_handler.h"

void *listenForMessages(void *);

int main(int argc, char *argv[]) {
	
	if (argc < 3) {
		fprintf(stderr, "Usage: %s (hostname) (port)\n", argv[0]);
		exit(1);
	}

	int port_num = atoi(argv[2]);
	
	// create client socket
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket < 0) {
		fprintf(stderr, "ERROR: could not open client socket");
		exit(1);
	}

	// struct to store information about the host
	struct hostent *server;
	server = gethostbyname(argv[1]);
	if (server == NULL) {
		fprintf(stderr, "ERROR: no such host\n");
		exit(1);
	}

	// specify an address and port for the socket to connect to
	struct sockaddr_in server_address;
	bzero((char *) &server_address, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port_num);
	bcopy((char *)server->h_addr, (char *)&server_address.sin_addr.s_addr, server->h_length);
	
	int connection_status = connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address));
	
	// check for error with the connection
	if (connection_status < 0) {
		fprintf(stderr, "ERROR: could not connect to the remote socket");
		exit(1);
	}
	
	// buffer to hold messages from client to be sent to the server
	char buffer_write[256];
	int conn_status = 0;
    pthread_t thread;
    pthread_create(&thread, NULL, listenForMessages, (void *)client_socket);

    printf("Welcome to the server! Begin chatting!\n");
	// write to the server
	while (conn_status >= 0) {
		bzero(buffer_write, 256);
		fgets(buffer_write, 255, stdin);
		conn_status = write(client_socket, buffer_write, strlen(buffer_write));
		if (conn_status < 0) {
			fprintf(stderr, "ERROR: could not write to the remote socket");
			exit(1);
		}
	}
	return 0;
}

// Function to listen for incoming messages in a separate thread
void *listenForMessages(void* arg) {
    char buffer_read[256];
    int conn_status = 0;
    int client_socket = (int)arg;
    while(conn_status >= 0) {
        bzero(buffer_read, 256);
		conn_status = read(client_socket, buffer_read, 255);
		if (conn_status < 0) {
			fprintf(stderr, "ERROR: could not read from remote socket");
			exit(1);
		}
		printf("%s\n", buffer_read);
    }

}
