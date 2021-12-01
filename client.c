#include <stdio.h>
#include "CSRSocket.c"
#define BUFFER 256

int main()
{
	SOCKET sock;
	int connect, sendReturn;
    char data[BUFFER]="";
    
    while(strcmp(data, "sair") != 0){
	    printf("\nDigite texto a ser enviado: ");
	    fgets(data, BUFFER, stdin);
	    data[strcspn(data, "\n")] = '\0'; // strip \n
	    
		printf("Tentando conexao...\n");
	    connect = conectar(&sock, "127.0.0.1", 8221);
		if(connect < 0)
	    	printf("Falha na conexao\n");
	    else 
	    	printf("OK\n");
	    
	    printf("Enviando mensagem...\n");
	    sendReturn = enviar(sock, data);
	    if(sendReturn != -1)
			printf("OK\n");
		else printf("Falha no envio da mensagem\n");
	}
    return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
