#include <stdio.h>
#include "CSRSocket.c"
#define BUFFER 256

int main()
{
    char data[BUFFER]="";
    
    while(strcmp(data, "sair") != 0){
	    printf("\nAguardando dados...");
	    receber(8221, data);
	    printf("\nDados recebidos: %s\n", data);
	}
    return 0;
}

