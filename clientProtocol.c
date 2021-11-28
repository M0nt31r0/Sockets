#include <stdio.h>
#include "CSRSocket.c"
#include <string.h>
#define BUFFER 256

int main(int argc, char *argv[]){
	int serverPort = 8221, clientPort = 8222, OK = 0;
	char msg[BUFFER] = "", cod[BUFFER] = "";
	SOCKET sock;
	while(1){
	
		printf("Tentando conectar na porta %i\n", serverPort);
		while(conectar(&sock, "127.0.0.1", serverPort) < 0);
		printf("Enviando mensagem PRODUTO\n");
		sleep(1);
		enviar(sock, "PRODUTO");
		printf("Ouvindo porta %i. Aguardando servidor...\n", clientPort);
		receber(clientPort, msg);
		printf("Mensagem do servidor: %s\n", msg);
		
		if(strcmp(msg, "OK") == 0){
			printf("Tentando conectar na porta %i\n", serverPort);
			while(conectar(&sock, "127.0.0.1", serverPort) < 0);
			printf("Digite o codigo do produto: ");
			fgets(cod, BUFFER, stdin);
			cod[strcspn(cod, "\n")] = '\0'; // strip newline from fgets
			enviar(sock, cod);
			printf("Ouvindo porta %i. Aguardando servidor...\n", clientPort);
			receber(clientPort, msg);
			if(strcmp(msg, "OK") == 0){
				printf("Produto encontrado!\n");
				while(conectar(&sock, "127.0.0.1", serverPort) < 0);
				enviar(sock, "NOME");
				receber(clientPort, msg);
				printf("Nome: %s\n",msg);
				while(conectar(&sock, "127.0.0.1", serverPort) < 0);
				enviar(sock, "FABRICANTE");
				receber(clientPort, msg);
				printf("Fabricante: %s\n",msg);
				while(conectar(&sock, "127.0.0.1", serverPort) < 0);
				enviar(sock, "PRECO");
				receber(clientPort, msg);
				printf("Preco: %s\n",msg);
				while(conectar(&sock, "127.0.0.1", serverPort) < 0);
				enviar(sock, "QUANTIDADE");
				receber(clientPort, msg);
				printf("Quantidade: %s\n",msg);
				while(conectar(&sock, "127.0.0.1", serverPort) < 0);
				enviar(sock, "FIM");
				receber(clientPort, msg);
				printf("Mensagem: %s\n",msg);
			}else{
				printf("Produto nao encontrado!\n");
			}
		}else{
			printf("Mensagem Invalida!\n");
		}
	}
	getchar();
	
}
