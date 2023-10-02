#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(int argc, char *argv[]){

	char *server_ip;
	int port;
	server_ip = argv[1];
	port = atoi(argv[2]);

	// create a socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	// specify an address of the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	/* server_address.sin_addr.s_addr = INADDR_ANY; */
	server_address.sin_addr.s_addr = server_ip;

	// check connection
	int connection_status = connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address));
	if(connection_status == -1){
		printf("Error\n");
		return 0;
	}

	// receive data from the server
	char server_response[256];
	recv(network_socket, server_response, sizeof(server_response), 0);

	// print out the server response
	printf("The server response: %s\n", server_response);

	// close the socket
	close(network_socket);
	return 0;
}
