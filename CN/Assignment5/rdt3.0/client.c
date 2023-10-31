#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PACKET_SIZE 	(7)
#define MESSAGE_SIZE  	(200)
#define RDT 			(1)

char message[MESSAGE_SIZE];
char seq_num[2] = "0";

typedef struct thread_var_receive{
	char *pack;
	int s;
}thread_var_receive;

void make_packet(char *message, char *packet, int str_size, int j){
	int i;
	for(i = 0; i < str_size && i < 5; i++){
		packet[i] = message[i + j];
	}
	packet[i] = '\0';
	return; 
}

void timer(void *s){
	int *ptimeout= (int*)s;
	clock_t initial = clock(), difference = 0;
	int time;
	do{
		difference = clock() - initial;
		time = difference/CLOCKS_PER_SEC;
		/* printf("%d\t%d\n", time, RDT); */
	}while(time <= RDT);
	*ptimeout = 1;
	pthread_cancel(pthread_self());
	return;
}

void receive(void *temp){
	thread_var_receive t = *(thread_var_receive*)temp;
	if(recv(t.s, t.pack, sizeof(2), 0) < 0){
		perror("Error in receiving packet: ");
		exit(0);
	}
	pthread_cancel(pthread_self());
}

// unreliable data transfer
void udt_send(int s, char *packet, int size){
	char IS_ACK = -1;
	int timeout = 0;
	// check NAK and ACK received
	while(1){
		if(send(s, packet, size, 0) < 0){
			perror("Error. sending data to server: ");
			exit(0);
		}
		pthread_t tid1, tid2;
		thread_var_receive temp;
		temp.s = s;
		temp.pack = &IS_ACK;

		IS_ACK = -1;
		timeout = 0;
		if(pthread_create(&tid1, NULL, (void*)&timer, (void*)&timeout)){
			perror("Error creating thread");
		}
		if(pthread_create(&tid2, NULL, (void*)&receive, (void*)&temp)){
			perror("Error creating thread");
		}
		while(IS_ACK == -1 && !timeout); 
		pthread_cancel(tid1);
		pthread_cancel(tid2);
		/* if(recv(s, &IS_ACK, sizeof(IS_ACK), 0) < 0){ */
		/* 	perror("Error in receiving packet: "); */
		/* 	exit(0); */
		/* } */
		if(IS_ACK != -1){
			if(IS_ACK == seq_num[0]){
				printf("ACK received -  Packet transferred - ACK no %c\n", IS_ACK);
				break;
			}
			else{
				printf("ACK received -  Packet transferred - ACK no %c\n", IS_ACK);
			}
		}
		else{
			printf("ACK not received -  Packet lost - retransmitting\n");
		}

	};

	return;
}

void done(char *packet){
	strcpy(packet, "Done");
	return;
}

void update_seq_num(){
	/* printf("len: %d\n", strlen(message)); */
	if(seq_num[0] == '0'){
		seq_num[0] = '1';
	}
	else{
		seq_num[0] = '0';
	}
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
		strcat(message, seq_num);
		udt_send(s, message, sizeof(message));
		update_seq_num(seq_num);
		return -1;
	}
	for(i = 0; i < strlen(message); i = i + 5){
		make_packet(message, packet, strlen(message), i);
		/* printf("%s\t%s\n", seq_num, packet); */
		strcat(packet, seq_num);
		udt_send(s, packet, sizeof(packet));
		update_seq_num(seq_num);
		/* udt_send(s, message, sizeof(message)); */
	}
	done(packet);
	strcat(packet, seq_num);
	udt_send(s, packet, sizeof(packet));

	update_seq_num(seq_num);
	printf("Total %d packets transmitted\nPacket size - %d\n", i / 5 + 1, PACKET_SIZE-2);
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

		

