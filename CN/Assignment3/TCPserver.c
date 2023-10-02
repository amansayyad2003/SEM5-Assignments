#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){

	char *server_ip;
	int port;

	if(argc != 3){
		printf("Usage: %s <Server's address> <file name> \n", argv[0]);
		return 0;
	}

	// input from user
	server_ip = argv[1];
	port = atoi(argv[2]);

	// creating socket
	int s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if(s < 0){
		perror("socket");
		return 0;
	}

	// server address
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	if(inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0){
		printf("Error: Invalid ip\n");
		return 0;
	
	}

	// binding
	if(bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr))){
		perror("Error: bind");
		return 0;
	}
	listen(s, 1);

	// accepting and communicating
	int client_socket;
	char message[255];
	while(1){
		printf("\nWaiting for request ...\n");
		client_socket = accept(s, NULL, NULL);
		while(1){
			if(recv(client_socket, message, sizeof(message), 0) == -1){
				perror("Error: Receiving data to server");
				break;
			}
			if(strcmp("close\n", message) == 0){
				printf("Client closed connection\n");
				break;
			}
			printf("Client: %s\n", message);
			printf("Server: ");
			fgets(message, sizeof(message), stdin);
			if(send(client_socket, message, sizeof(message), 0) == -1){
				perror("Error: In sending data to client");
				break;
			}
			if(strcmp("close\n", message) == 0){
				break;
			}
		}
		close(client_socket);
	}

	// close socket
	close(s);
	
	return 0;
}

