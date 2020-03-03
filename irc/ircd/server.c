/*
 * server.c
 * CS3337
 * Written by: Marcus Goeckner
 * Professor McGregor
 * 2/21/2020
 *
 * Creates a TCP server socket that binds to an IP address and port to listen for connections
*/

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>

void *communicate(void *);

int main(int argc, char *argv[]) {
	// output error message if no port argument is provided 
	if (argc < 2) {
		fprintf(stderr, "ERROR: no port provided\n");
		exit(1);
	}

	int port_num = atoi(argv[1]);

	// create the server socket
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0) {
		fprintf(stderr, "ERROR: could not create server socket");
		exit(1);
	}

	// define server address and declare a client address to be used when accpeting connections
	struct sockaddr_in server_address, client_address;
	bzero((char *) &server_address, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port_num);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// bind the socket to the specified IP address and port
	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	
	// listen for connections
	listen(server_socket, 5);
	int client_len = sizeof(client_address);
	// infinite loop to continously accept connections	
	while(1) {
		// accept connections on the server socket and create new threads to deal with clients  
		int new_client_socket = accept(server_socket, (struct sockaddr *) &client_address, &client_len);
		if (new_client_socket < 0) {
			fprintf(stderr, "ERROR: could not accept new connection");
			exit(1);
		}
		pthread_t thread;
		pthread_create(&thread, NULL, communicate, (void *)new_client_socket);
	}
	return 0;
}

// function to communicate with each client in their own thread
void* communicate(void* arg) {
	char buffer[256];
	int conn_status;
	int new_client_socket = (int)arg;
	while(1) {
		bzero(buffer, 256);
		conn_status = read(new_client_socket, buffer, 255);
		if (conn_status < 0) {
			fprintf(stderr, "ERROR: could not read from socket");
			exit(1);
		}
		printf("Message from a client: %s\n", buffer);
		conn_status = write(new_client_socket, "The server got your message\n", 255);
		if (conn_status < 0) {
			fprintf(stderr, "ERROR: could not  write to socket");
			exit(1);
		}
	}
	return 0;
}
