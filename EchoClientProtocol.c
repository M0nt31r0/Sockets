#include <stdio.h>
#include "CSRSocket.c"
#include <string.h>
#define BUFFER 256

int main(int argc, char *argv[]){
	int serverPort = 8240, OK = 0, intPort;
	char data[BUFFER] = "", clientPort[BUFFER] = "", *token;
	SOCKET sock;
	
	while(!OK){
		printf("Digite a porta resposta: ");
		scanf("%s", clientPort);
		intPort = atoi(clientPort);
		if(intPort > 0 && intPort < 65535) OK = 1;
		else printf("Erro [%i] porta invalida.\n");
	}
	while(1){
		printf("Tentando conectar na porta %i\n", serverPort);
		while(conectar(&sock, "127.0.0.1", serverPort) < 0);
		printf("Digite um texto qualquer, para sair digite [SAIR]: ");
		fgets(data, BUFFER, stdin);
		data[strcspn(data, "\n")] = '\0';
		strcat(data, " ");
		strcat(data, clientPort);
		enviar(sock, data);
		printf("Ouvindo porta %i. Aguardando servidor...\n", intPort);
		receber(intPort, data);
		printf("Mensagem recebida: %s\n", data);
		token = strtok(data, " ");
		if(strcmp(token, "SAIR") == 0 || strcmp(token, "sair") == 0){
			printf("Finalizando programa...\n");
			sleep(1);
			exit(1);
		}	
	}
	
}
