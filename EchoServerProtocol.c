#include <stdio.h>
#include "CSRSocket.c"
#include <string.h>
#include <stdlib.h>
#define BUFFER 255

int main(int argc, char *argv[]){
	int serverPort = 8240, clientPort;
	char data[BUFFER] = "", *peace, *word;
	SOCKET sock;

	while(1){
		printf("Ouvindo na porta %i. Aguardando mensagem\n", serverPort);
		receber(serverPort, data);
		int chk = 0;
		char *p = strrchr(data, ' ');
		if(p && *(p+1))
			word = p+1;
		clientPort = atoi(word);
		while(conectar(&sock, "127.0.0.1", clientPort) < 0);
		enviar(sock, data);
		sleep(1);		
	}
	return 0;
}
