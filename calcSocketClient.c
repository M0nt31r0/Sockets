#include <stdio.h>
#include "CSRSocket.c"
#define BUFFER 256

int main(int argc, char *argv[]){
	SOCKET sock;
	int serverPort, clientPort, num[2];
	char operation = ' ', data[BUFFER] = "";
	
	serverPort = atoi(argv[1]);
	clientPort = atoi(argv[2]);
	
	while(operation != 'S'){
		system("cls");
		printf("\nEscolha uma opcao\n\n");
		printf("\n(+) Somar");
		printf("\n(-) Subtrair");
		printf("\n(*) Multiplicar");
		printf("\n(/) Dividir");
		printf("\n(S) Sair\n");
		scanf("%c", &operation);
		getchar(); // clear buffer
		
		if(operation != 'S'){
			if(operation == '+' || operation == '-' || operation == '*' || operation == '/'){
				printf("Digite o primeiro numero: ");
				scanf("%i", &num[0]);
				printf("Digite o segundo numero: ");
				scanf("%i", &num[1]);
				
				getchar();
				
				printf("Conectando na porta %i\n", serverPort);
				sprintf(data, "INICIO %i", clientPort);
				while(conectar(&sock, "127.0.0.1", serverPort) < 0);
				enviar(sock, data);
				
				printf("Aguardando resposta %i\n", clientPort);
				receber(clientPort, data);
				
				if(strcmp(data, "OK") == 0){
					sprintf(data, "PARTE1 %i", num[0]);
					while(conectar(&sock, "127.0.0.1", serverPort) < 0);
					enviar(sock, data);
					receber(clientPort, data);
					if(strcmp(data, "OK") == 0){
						sprintf(data, "PARTE2 %i", num[1]);
						while(conectar(&sock, "127.0.0.1", serverPort) < 0);
						enviar(sock, data);
						receber(clientPort, data);
						if(strcmp(data, "OK") == 0){
							sprintf(data, "OPERACAO %c", operation);
							while(conectar(&sock, "127.0.0.1", serverPort) < 0);
							enviar(sock, data);
							receber(clientPort, data);
							if(strcmp(data, "ERRO") != 0){
								printf("Resultado da (%c): %s\n", operation, data);
							}else printf("ERRO <4>\n");
						}else printf("ERRO <3>\n");
					}else printf("ERRO <2>\n");
				}else printf("ERRO <1>\n");			
			}else printf("ERRO. Opcao invalida\n");
			
			printf("Pressione <ENTER> para continuar...\n");
			getchar();
		}
	}
}
