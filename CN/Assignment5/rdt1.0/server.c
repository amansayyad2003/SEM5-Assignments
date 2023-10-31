#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <arpa/inet.h>

char message[100];
int packet_size = 5;

void make_packet(char *message, char *packet, int str_size, int j){
	for(int i = 0; i < str_size && i < packet_size; i++){
		packet[i] = message[i + j];
	}
	return;
}

// unreliable data transfer
void udt_send(int s, char *packet, int size){
	if(send(s, packet, size, 0) < 0){
		perror("Error. sending data to server: ");
		exit(0);
	}
	return;
}

void done(char *packet){
	strcpy(packet, "Done");
	return;
}

// reliable data transfer
int rdt_send(int s){
	char packet[6];

	printf("server: ");
	fgets(message, sizeof(message), stdin);
	for(int i = 0; i < strlen(message); i = i + 5){
		make_packet(message, packet, strlen(message), i);
		/* printf("%s\n", packet); */
		udt_send(s, packet, sizeof(packet));
		/* udt_send(s, message, sizeof(message)); */
	}
	done(packet);
	udt_send(s, packet, sizeof(packet));
	return 0;
}

// reliable data receive
int rdt_recv(int s){
	char packet[6] = "", message[100] = "";
	printf("client: ");
	for(int i = 0; strcmp(packet,"Done") != 0; i += 5){
		strcat(message, packet);
		if(recv(s, packet, sizeof(packet), 0) < 0){
		/* if(recv(s, message, sizeof(message), 0) < 0){ */
			perror("Error in receiving packet: ");
			exit(0);
		}
		/* printf("\npacket: %s\n", packet); */
		/* printf("messae: %s\n", message); */
	}
	if(message == "Exit"){
		return -1;
	}
	printf("%s\n", message);
	return 0;
}

int main(int argc, char *argv[]){
	char *ip = argv[1];
	int port = atoi(argv[2]);

	int s;
	struct sockaddr_in server_addr;
	
	// create socket
	s = socket(AF_INET, SOCK_STREAM, 0);
	if(s < 0){
		perror("socket: ");
		exit(0);
	}

	// assign server address 
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	if(inet_pton(AF_INET, ip, &server_addr.sin_addr) < 0){
		perror("invalid ip: ");
		exit(0);
	}

	if(bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		perror("bind");
		exit(0);
	}
	
	listen(s, 5);
	
	int p, len;

	while(1){
		printf("Waiting for request ... \n");
		/* len = sizeof(server_addr); */
		p = accept(s, NULL, NULL);
		while(1){
			if(rdt_recv(p) < 0){
				break;
			}
			if(rdt_send(p) < 0){
				break;
			}
		}
		close(p);
	}

	close(s);
	return 0;
}
