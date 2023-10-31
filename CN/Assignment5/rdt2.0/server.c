#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#define PACKET_SIZE  6
#define MESSAGE_SIZE  200

char message[PACKET_SIZE];
int corrupt_num = 1;

void make_packet(char *message, char *packet, int str_size, int j){
	for(int i = 0; i < str_size && i < PACKET_SIZE - 1; i++){
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
	char packet[PACKET_SIZE];

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

int corrupt(char *packet){
	/*time_t times;
	double rand_num;
	srand(time(&times));
	rand_num = rand() % 10;
	if(rand_num < 2){
		return 1;
	}
	else{
		return 0;
	}*/
	if(corrupt_num % 7 == 0){
		corrupt_num++;
		return 1;
	}
	corrupt_num++;
	return 0;
}

// reliable data receive
int rdt_recv(int s){
	char packet[PACKET_SIZE] = "", message[MESSAGE_SIZE] = "", ACK = 1;
	int i;
	printf("---------------------------------------------------------------\n");
	for(i = 0; strcmp(packet,"Done") != 0; i += 5){
		strcat(message, packet);
		if(recv(s, packet, sizeof(packet), 0) < 0){
			perror("Error in receiving packet: ");
			exit(0);
		}
		if(corrupt(packet)){
			ACK = 0;
			strcpy(packet, "");
		}
		else{
			ACK = 1;
		}
		printf("Packet received - Acknowledgement sended\n");
		udt_send(s, &ACK, sizeof(ACK));
		if(i == 0 && ACK && strcmp(packet, "Exit\n") == 0){
			udt_send(s, &ACK, sizeof(ACK));
			return -1;
		}
		/* printf("\npacket: %s\n", packet); */
		/* printf("messae: %s\n", message); */
	}
	printf("Total %d packets received\nPacket Size - %d\n\n", i / 5, PACKET_SIZE-1);
	/* if(message == "Exit\n"){ */
	/* 	return -1; */
	/* } */
	printf("client: %s", message);
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
		printf("\nWaiting for request ... \n");
		/* len = sizeof(server_addr); */
		p = accept(s, NULL, NULL);
		while(1){
			if(rdt_recv(p) < 0){
				break;
			}
			/* if(rdt_send(p) < 0){ */
			/* 	break; */
			/* } */
		}
		close(p);
	}

	close(s);
	return 0;
}
