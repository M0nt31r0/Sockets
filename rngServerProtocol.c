#include <stdio.h>
#include "CSRSocket.c"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define BUFFER 255

int main(int argc, char *argv[]){
	int serverPort = 8140, rng, clientPort;
	char data[BUFFER] = "", *peace;
	SOCKET sock;
	srand(time(NULL));
	
	while(1){
		printf("Ouvindo na porta %i. Aguardando mensagem\n", serverPort);
		receber(serverPort, data);
		peace = strtok(data, " ");
		if(strcmp(peace, "DIGA_UM_NUMERO") == 0){
			peace = strtok(NULL," ");
			clientPort = atoi(peace);
			rng = rand() % 10000;
			sprintf(data, "%d", rng);
			while(conectar(&sock, "127.0.0.1", clientPort) < 0);
			enviar(sock, data);
			sleep(1);
		}	
	}
	return 0;
}
