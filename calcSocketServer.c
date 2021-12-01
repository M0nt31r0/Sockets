#include <stdio.h>
#include "CSRSocket.c"
#define BUFFER 256

int main(int argc, char *argv[]){
	SOCKET sock;
	int serverPort, clientPort, num[2], ok = 0, result;
	char *token, data[BUFFER] = "";
	
	serverPort = atoi(argv[1]);
	while(1){
		while(!ok){
			printf("Aguardando conexao na porta %i\n", serverPort);
			receber(serverPort, data);
			token = strtok(data, " ");
			if(strcmp(token, "INICIO") == 0){
				token = strtok(NULL, " ");
				clientPort = atoi(token);
				
				printf("Tentando conexao na porta %i\n", clientPort);
				while(conectar(&sock, "127.0.0.1", clientPort) < 0);
				enviar(sock, "OK");
				ok = 1;
			}
		}
		ok = 0;
		while(!ok){
			printf("Aguardando conexao na porta %i\n", serverPort);
			receber(serverPort, data);
			printf("Tentando conexao na porta %i\n", clientPort);
			while(conectar(&sock, "127.0.0.1", clientPort) < 0);
			token = strtok(data, " ");
			if(strcmp(token, "PARTE1") == 0){
				token = strtok(NULL, " ");
				num[0] = atoi(token);
				enviar(sock, "OK");
				ok = 1;
			}else enviar(sock, "ERRO");
		}
		ok = 0;
		while(!ok){
			printf("Aguardando conexao na porta %i\n", serverPort);
			receber(serverPort, data);
			printf("Tentando conexao na porta %i\n", clientPort);
			while(conectar(&sock, "127.0.0.1", clientPort) < 0);
			token = strtok(data, " ");
			if(strcmp(token, "PARTE2") == 0){
				token = strtok(NULL, " ");
				num[1] = atoi(token);
				enviar(sock, "OK");
				ok = 1;
			}else enviar(sock, "ERRO");
		}
		ok = 0;
		while(!ok){
			printf("Aguardando conexao na porta %i\n", serverPort);
			receber(serverPort, data);
			printf("Tentando conexao na porta %i\n", clientPort);
			while(conectar(&sock, "127.0.0.1", clientPort) < 0);
			token = strtok(data, " ");
			printf("%s\n",data);
			if(strcmp(token, "OPERACAO") == 0){
				token = strtok(NULL, " ");
				switch(token[0]){
					case '+':
						result = num[0] + num[1];
						break;
					case '-':
						result = num[0] - num[1];
						break;
					case '*':
						result = num[0] * num[1];
						break;
					case '/':
						result = num[0] / num[1];
						break;
				}
				printf("Resultado: %i %c %i = %i\n", num[0], token[0], num[1], result);
				sprintf(data, "%i", result);
				enviar(sock, data);
				ok = 1;
			}else enviar(sock, "ERRO");
		}		
		ok = 0;
	}
	getchar();
	return 0;
}
