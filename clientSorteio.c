#include <stdio.h>
#include <stdlib.h>
#include "CSRSocket.c"
#include <string.h>
#define BUFFER 16

int main(int argc, char *argv[]){
	int serverPort = 8221, port;
	char msg[BUFFER] = "";
	SOCKET sock;
	
	while(1){
		port = atoi(argv[1]);
		strcat(msg, "PARTICIPAR ");
		strcat(msg, argv[1]);
		printf("Tentando conexao na porta %i\n", serverPort);
		while(conectar(&sock, "127.0.0.1", serverPort) < 0);
		printf("Enviando mensagem [%s]\n", msg);
		enviar(sock, msg);
		
		printf("Ouvindo porta %s. Aguardando servidor...\n", argv[1]);
		receber(port, msg);
		printf("%s\n", msg);
	}
	getchar();
	
}
