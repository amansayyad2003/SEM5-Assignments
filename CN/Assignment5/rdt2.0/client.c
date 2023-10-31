#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#define PACKET_SIZE 6
#define MESSAGE_SIZE  200

char message[MESSAGE_SIZE];

void make_packet(char *message, char *packet, int str_size, int j){
	for(int i = 0; i < str_size && i < PACKET_SIZE - 1; i++){
		packet[i] = message[i + j];
	}
	return;
}

// unreliable data transfer
void udt_send(int s, char *packet, int size){
	char IS_ACK;
	// check NAK and ACK received
	while(1){
		if(send(s, packet, size, 0) < 0){
			perror("Error. sending data to server: ");
			exit(0);
		}
		if(recv(s, &IS_ACK, sizeof(IS_ACK), 0) < 0){
			perror("Error in receiving packet: ");
			exit(0);
		}
		if(IS_ACK){
			printf("ACK received -  Packet transferred\n");
			break;
		}
		else{
			printf("NAK received -  Packet resending\n");
		}

	};

	return;
}

void done(char *packet){
	strcpy(packet, "Done");
	return;
}

// reliable data transfer
int rdt_send(int s){
	char packet[PACKET_SIZE];
	int i;

	printf("---------------------------------------------------------------\n");
	printf("Client: ");
	fgets(message, sizeof(message), stdin);
	if(strcmp(message, "Exit\n") == 0){
		udt_send(s, message, sizeof(message));
		return -1;
	}
	for(i = 0; i < strlen(message); i = i + 5){
		make_packet(message, packet, strlen(message), i);
		/* printf("%d - %s\n",i,  packet); */
		udt_send(s, packet, sizeof(packet));
		/* udt_send(s, message, sizeof(message)); */
	}
	done(packet);
	udt_send(s, packet, sizeof(packet));
	printf("Total %d packets transmitted\nPacket size - %d\n", i / 5 + 1, PACKET_SIZE-1);
	/* printf("All packets transferred !!! \n\n"); */
	return 0;
}

// reliable data receive
int rdt_recv(int s){
	char packet[PACKET_SIZE] = "", message[MESSAGE_SIZE] = "";
	printf("server: ");
	for(int i = 0; strcmp(packet,"Done") != 0; i += 5){
		strcat(message, packet);
		if(recv(s, packet, sizeof(packet), 0) < 0){
		/* if(recv(s, message, sizeof(message), 0) < 0){ */
			perror("Error in receiving packet: ");
			exit(0);
		}
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

	// connect
	if(connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		perror("connect: ");
		exit(0);
	}
	
	printf("Connected to server\n");

	// send data
	while(1){
		if(rdt_send(s) < 0){
			break;
		}
		/* if(rdt_recv(s) < 0){ */
		/* 	break; */
		/* } */
	}

	close(s);
	return 0;
}

		

