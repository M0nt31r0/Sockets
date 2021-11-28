#include <stdio.h>
#include "CSRSocket.c"
#include <string.h>
#define BUFFER 256

int main(int argc, char *argv[]){
	int serverPort = 8140, clientPort = 8120;
	char data[BUFFER] = "", *i;
	SOCKET sock;
	
	
	while(1){
	
		printf("Tentando conectar na porta %i\n", serverPort);
		while(conectar(&sock, "127.0.0.1", serverPort) < 0);
		printf("Enviando mensagem DIGA_UM_NUMERO 8120\n");
		sleep(1);
		enviar(sock, "DIGA_UM_NUMERO 8120");
		printf("Ouvindo porta %i. Aguardando servidor...\n", clientPort);
		receber(clientPort, data);
		printf("Numero gerado: %s\n", data);	
	}
	getchar();
	
}
