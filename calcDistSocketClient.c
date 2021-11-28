#include <stdio.h>
#include "CSRSocket.c"
#include <string.h>
#define BUFFER 256

int main(int argc, char *argv[]){
	int serverPort, clientPort, i;
	float Xa, Ya, Xb, Yb;
	char data[BUFFER] = "", choice[1] = "";
	SOCKET sock;
	serverPort = atoi(argv[1]);
	clientPort = atoi(argv[2]);
	while(1){
		printf("Tentando conectar na porta %i\n", serverPort);
		printf("Primeiro ponto: \n");
		printf("Xa: ");
		scanf("%f", &Xa);
		printf("Ya: ");
		scanf("%f", &Ya);
		printf("Segundo ponto: \n");
		printf("Xb: ");
		scanf("%f", &Xb);
		printf("Yb: ");
		scanf("%f", &Yb);
		i = sprintf(data, "%d ", clientPort);
		i += sprintf(data+i, "%f ", Xa);
		i += sprintf(data+i, "%f ", Ya);
		i += sprintf(data+i, "%f ", Xb);
		i += sprintf(data+i, "%f", Yb);
		while(conectar(&sock, "127.0.0.1", serverPort) < 0);
		enviar(sock, data);
		printf("Ouvindo porta %i. Aguardando resposta do servidor...\n", clientPort);
		receber(clientPort, data);
		printf("Distancia: %s\n", data);
		receber(clientPort, data);
		printf("%s",data);
		scanf("%s", choice);
		while(conectar(&sock, "127.0.0.1", serverPort) < 0);
		enviar(sock, choice);
		receber(clientPort, data);
		if(strcmp(data, "abort") == 0){
			printf("Finalizando Programa...\n");
			sleep(2);
			break;
		}else printf("Continuando Programa...\n");
		
	}
	getchar();
	
}
