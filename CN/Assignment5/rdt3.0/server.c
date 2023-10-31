#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#define PACKET_SIZE  7
#define MESSAGE_SIZE  200
#define RDT 1.2

char message[PACKET_SIZE];
char seq_num = '1';
int corrupt_num = 0;

void make_packet(char *message, char *packet, int str_size, int j){
	for(int i = 0; i < str_size && i < 5; i++){
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
	/* return 0; */
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

int is_duplicate(char seq_number){
	if(seq_number == seq_num){
		return 1;
	}
	else{
		return 0;
	}
}

void set_timer(){
	/* printf("%d\n", corrupt_num); */
	if(corrupt_num % 8 == 0){
		clock_t initial = clock(), difference;
		int time;
		do{
			difference = clock() - initial;
			time = difference/ CLOCKS_PER_SEC;
		}while(time <= RDT);
	}
	/* corrupt_num++; */
	return;
}
// reliable data receive
int rdt_recv(int s){
	char packet[PACKET_SIZE] = "", message[MESSAGE_SIZE] = "", ACK = 1, seq_num_temp;
	int i;
	printf("---------------------------------------------------------------\n");
	for(i = 0; strcmp(packet,"Done") != 0; i += 5){
		strcat(message, packet);
		if(recv(s, packet, sizeof(packet), 0) < 0){
			perror("Error in receiving packet: ");
			exit(0);
		}
		seq_num_temp = packet[strlen(packet)-1];
		packet[strlen(packet)-1] = '\0';
		if(corrupt(packet)){
			ACK = seq_num;
			strcpy(packet, "");
		}
		else{
			/* ACK = seq_num_temp; */
			if(is_duplicate(seq_num_temp)){
				ACK = (seq_num_temp-'0'+1)%2 + '0';
				strcpy(packet, "");
				printf("Duplicate Packet received - Packet discarded - Seq no. %c\n", seq_num);
			}
			else{
				ACK = seq_num_temp;
				seq_num = seq_num_temp;
				printf("Packet received - Acknowledgement sended - Seq no. %c\n", seq_num);
			}
			if(strcmp(packet, "Exit\n") == 0){
				udt_send(s, &ACK, sizeof(ACK));
				return -1;
			}
		}
		set_timer();
		udt_send(s, &ACK, sizeof(ACK));
	}
	printf("Total %d packets received\nPacket Size - %d\n\n", i / 5, PACKET_SIZE-2);
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
