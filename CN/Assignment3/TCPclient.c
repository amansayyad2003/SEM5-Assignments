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
		perror("socket\n");
		return 0;
	}

	// assign address
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	if(inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0){
		printf("Invalid ip\n");
		return 0;
	}

	// connect
	if(connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		perror("Connect");
		return 0;
	}
	printf("Connected to server ...\n");

	//take user input
	char message[255];
	printf("Enter something\n");
	while(1){
		printf("Client: ");
		fgets(message, sizeof(message), stdin);
		if(send(s, message, sizeof(message), 0) == -1, 0){
			perror("Error: In sending data to server");
			break;
		}
		if(strcmp("close\n", message) == 0){
			break;
		}
		if(recv(s, message, sizeof(message), 0) == -1, 0){
			perror("Error: Receiving data to client");
			break;
		}
		if(strcmp("close\n", message) == 0){
			printf("Server closed connection\n");
			break;
		}
		printf("Server: %s\n", message);
	}

	// close socket
	close(s);
	return 0;
}


