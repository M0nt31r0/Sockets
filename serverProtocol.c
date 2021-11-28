#include <stdio.h>
#include "CSRSocket.c"
#include <string.h>
#include <stdlib.h>
#define BUFFER 256

struct product{
		char cod[BUFFER];
		char name[BUFFER];
		char fab[BUFFER];
		char price[BUFFER];
		char qty[BUFFER];
};
struct product details;
int OK = 0;
int FindProductFromFile(char *msg){
	FILE *archive = fopen("data.txt", "r");
	int found;
	printf("%s",msg);
	if(archive == NULL){
		perror("Erro ao tentar abrir arquivo.\n");
		exit(EXIT_FAILURE);
	}else{
		while(!feof(archive)){
			fscanf(archive,"%s %s %s %s %s\n",&details.cod, &details.name, &details.fab, &details.price, &details.qty);
			if(strcmp(msg, details.cod) == 0){
				found = 1;
				break;
			}
			else{
				found = 0;
			}
		}
	}
	fclose(archive);
	return found;
}
void SaveDetailsFromProduct(char *request, int clientPort){
	SOCKET sock;
	while(conectar(&sock, "127.0.0.1", clientPort) < 0);
	printf("Comando recebido: %s. Enviando resposta na porta %i\n", request, clientPort);
	if(strcmp(request, "NOME") == 0) enviar(sock, details.name);
	else if(strcmp(request, "FABRICANTE") == 0) enviar(sock, details.fab);
	else if(strcmp(request, "PRECO") == 0) enviar(sock, details.price);
	else if(strcmp(request, "QUANTIDADE") == 0) enviar(sock, details.qty);
	else if(strcmp(request, "FIM") == 0){
		OK = 1;
		enviar(sock, "OK");
	}
	else enviar(sock, "ERRO");
}
int main(int argc, char *argv[]){
	int serverPort = 8221, clientPort = 8222;
	char msg[BUFFER] = "";
	SOCKET sock;
	
	while(1){
		while(!OK){
			printf("1 - Ouvindo na porta %i. Aguardando mensagem...\n", serverPort);
			receber(serverPort, msg);
			while(conectar(&sock, "127.0.0.1", clientPort) < 0);
			
			if(strcmp(msg, "PRODUTO") == 0){
				enviar(sock, "OK");
				OK = 1;
			}else{
				enviar(sock, "ERRO");
			}
		}
		OK = 0;
		while(!OK){
			printf("2 - Ouvindo na porta %i. Aguardando Mensagem...\n", serverPort);
			receber(serverPort, msg);
			while(conectar(&sock, "127.0.0.1", clientPort) < 0);
			printf("Codigo recebido: %i\n", atoi(msg));
			if(FindProductFromFile(msg)){
				printf("Produto encontrado!\n");
				enviar(sock, "OK");
				OK = 1;
			}else{
				printf("Produto nao encontrado!\n");
			}
		}
		OK = 0;
		while(!OK){
			printf("2 - Ouvindo na porta %i. Aguardando Mensagem...\n", serverPort);
			receber(serverPort, msg);
			SaveDetailsFromProduct(msg, clientPort);
		}
		OK = 0;
	}
	getch();
}
