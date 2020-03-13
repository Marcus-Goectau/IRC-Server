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
	
	// buffer to hold messages between server and client
	char buffer[256];
	int conn_status;

	// communicate with server
	while (1) {
		printf("Enter your message: ");
		bzero(buffer, 256);
		fgets(buffer, 255, stdin);
		conn_status = write(client_socket, buffer, strlen(buffer));
		if (conn_status < 0) {
			fprintf(stderr, "ERROR: could not write to the remote socket");
			exit(1);
		}
		bzero(buffer, 256);
		conn_status = read(client_socket, buffer, 255);
		if (conn_status < 0) {
			fprintf(stderr, "ERROR: could not read from remote socket");
			exit(1);
		}
		printf("%s\n", buffer);
	}
	return 0;
}
