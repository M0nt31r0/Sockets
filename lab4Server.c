#include <stdio.h>
#include <stdlib.h>
#include "CSRSocket.c"
#include <string.h>
#define MAX 2
#define BUFFER 255

int main(int argc, char *argv[]){
	int serverPort, counter = 0, clientPort, i, clients[MAX], num[MAX], hand[MAX], OK = 0;
	char *token, msg[BUFFER] = "";
	SOCKET sock;
	serverPort = atoi(argv[1]);
	while(1){
		while(counter < MAX){
			printf("Aguardando jogadores...\n", serverPort);
			receber(serverPort, msg);
			token = strtok(msg, " ");
			if(strcmp(token, "PARTICIPAR") == 0){
				token = strtok(NULL, " ");
				clientPort = atoi(token);
				clients[counter] = clientPort;
				counter++;
				while(conectar(&sock, "127.0.0.1", clientPort) < 0);
				enviar(sock, "OK");
			}else{
				while(conectar(&sock, "127.0.0.1", clientPort) < 0);
				enviar(sock, "ERRO");
			} 
		}
		OK = 0;
		while(!OK){
			for(i = 0; i < MAX; i++){
				while(conectar(&sock, "127.0.0.1", clients[i]) < 0);
				printf("Enviando mensagem [TIPO] na porta %i\n",clients[i]);
				enviar(sock, "TIPO");
				receber(serverPort, msg);
				printf("Mensagem recebida na porta %i: %s\n", clients[i], msg);
				if(strcmp(msg, "PAR") == 0){
					hand[i] = 0;
					while(conectar(&sock, "127.0.0.1", clients[i]) < 0);
					enviar(sock, "OK");
				}else if(strcmp(msg, "IMPAR") == 0){
					hand[i] = 1;
					while(conectar(&sock, "127.0.0.1", clients[i]) < 0);
					enviar(sock, "OK");
				}
				else{
					hand[i] = -1;
					while(conectar(&sock, "127.0.0.1", clients[i]) < 0);
					enviar(sock, "ERRO");
				}
			}
			if(hand[0] != hand[1] && hand[0] != -1 && hand[1] != -1){
				for(i = 0; i < MAX; i++){
					while(conectar(&sock, "127.0.0.1", clients[i]) < 0);
					enviar(sock, "NUMERO");
					receber(serverPort, msg);
					num[i] = atoi(msg);
					printf("Numero recebido da porta %i: %d\n", clients[i],hand[i]);
					while(conectar(&sock, "127.0.0.1", clients[i]) < 0);
					enviar(sock, "OK");
				}
				OK = 1;
			}else {
				while(conectar(&sock, "127.0.0.1", clients[i]) < 0);
				enviar(sock, "ERRO");
				OK = 0;
			}
		}
		OK = 0;
		counter = 0;
		while(!OK){
			int sum = num[0] + num[1];
			for(i = 0; i < MAX; i++){
				while(conectar(&sock, "127.0.0.1", clients[i]) < 0);
				if(sum % 2 == 0){
					if(hand[i] == 0) enviar(sock, "GANHADOR");
					else enviar(sock, "PERDEDOR");
				}else{
					if(hand[i] == 1) enviar(sock, "GANHADOR");
					else enviar(sock, "PERDEDOR");
				}
			}
			OK = 1;
		}
		/*while(!OK){
			int sum = num[0] + num[1];
			if(sum % 2 == 0){
				while(conectar(&sock, "127.0.0.1", clients[0]) < 0);
			}
		}*/
		//int winner = rand() % MAX_CLIENTS;
		/*for(i = 0; i < MAX_CLIENTS; i++){
			// conecta nas portas individualmente
			while(conectar(&sock, "127.0.0.1", clients[i]) < 0);
			if(winner == i) enviar(sock, "GANHADOR");
			else enviar(sock, "PERDEDOR");
			sleep(1);
		}*/
	}
	return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
