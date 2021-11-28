#include <stdio.h>
#include <stdlib.h>
#include "CSRSocket.c"
#include <string.h>
#include <time.h>
#define MAX_CLIENTS 3
#define BUFFER 16

int main(int argc, char *argv[]){
	const int serverPort = 8221;
	int counter = 0, clients[MAX_CLIENTS], clientPort, raffle = 0, i;
	char *data, msg[BUFFER] = "";
	SOCKET sock;
	srand(time(NULL));
	while(1){
		while(counter < MAX_CLIENTS){
			printf("Aguardando jogadores... Contagem: %i.\n", serverPort);
			receber(serverPort, msg);
			data = strtok(msg, " ");
			data = strtok(NULL, " ");
			clientPort = atoi(data);

			clients[counter] = clientPort;
			counter++;
			sleep(1);
		}
		printf("SORTEANDO...\n");
		sleep(2);
		int winner = rand() % MAX_CLIENTS;
		for(i = 0; i < MAX_CLIENTS; i++){
			// conecta nas portas individualmente
			while(conectar(&sock, "127.0.0.1", clients[i]) < 0);
			if(winner == i) enviar(sock, "GANHADOR");
			else enviar(sock, "PERDEDOR");
			sleep(1);
		}
		counter = 0;
		printf("Sorteio terminou! Aguardando novos jogadores\n\n");
	}
}
