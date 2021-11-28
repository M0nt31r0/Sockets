#include <stdio.h>
#include "CSRSocket.c"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define BUFFER 255

int main(int argc, char *argv[]){
	int serverPort, clientPort, result = 0;
	float num[4];
	char *token, data[BUFFER] = "";
	SOCKET sock;
	serverPort = atoi(argv[1]);
	while(1){
		int i = 0;
		printf("Ouvindo na porta %i. Aguardando mensagem\n", serverPort);
		receber(serverPort, data);
		token = strtok(data, " ");
		clientPort = atoi(token);

		while(token != NULL){
			token = strtok(NULL, " ");
			num[i] = atof(token);
			i++;
		}
		float distance = sqrt(pow(num[2]-num[0], 2)+pow(num[3]-num[1],2));
		printf("Distancia: %f\n", distance);
		printf("Enviando Resposta ao cliente na porta %i\n", clientPort);
		while(conectar(&sock, "127.0.0.1", clientPort) < 0);
		sprintf(data, "%f", distance);
		enviar(sock, data);
		sleep(1);
		while(conectar(&sock, "127.0.0.1", clientPort) < 0);
		enviar(sock, "Deseja continuar? [S/N]: ");
		receber(serverPort, data);
		while(conectar(&sock, "127.0.0.1", clientPort) < 0);
		if(strcmp(data, "n") == 0 || strcmp(data, "N") == 0){
			enviar(sock, "abort");
		}else enviar(sock, "continue");
		sleep(1);
	}
	return 0;
}
