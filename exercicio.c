#include <stdio.h>
#include <windows.h>
#include "CSRSocket.c"
#define MAX 255

DWORD WINAPI portclient(LPVOID param){
	long int value = (int) param;
	int conecta, retornoEnvio;
	char *msg;
	SOCKET sock;
	conecta = conectar(&sock, "127.0.0.1", 8221);
	if (conecta<0)
       printf("Erro na conexao!\n");
    else
        printf("Conexao efetuada!\n");
    fgets(msg, MAX, stdin);
    retornoEnvio = enviar(sock, msg);     
    if (retornoEnvio!=-1)
        printf("Mensagem enviada!\n");
    else
        printf("Erro no envio da mensagem!\n");	
    getch();
}
DWORD WINAPI portserver(LPVOID param){
	printf("\nAguardando...\n");
    char dados[256] = "";
	receber(8222, dados); 
    printf("\nDados recebidos: %s", dados);
}
int main(int argc, char *argv[]) {
	DWORD threadID;
	HANDLE thread[2];
	int i, client = 8221, server = 8222;
    if((argv[1], "1") == 0){
		client = 8222;
		server = 8221;
	}
    thread[0] = (HANDLE) CreateThread(NULL, 0 , portclient, client, CREATE_SUSPENDED, &threadID);
	thread[1] = (HANDLE) CreateThread(NULL, 0 , portserver, server, CREATE_SUSPENDED, &threadID);

	for(i = 0; i < MAX; i++)
		ResumeThread(thread[i]);
	for(i = 0; i < MAX; i++)
		WaitForSingleObject(thread[i], INFINITE);
	for(i = 0; i < MAX; i++)
		CloseHandle(thread[i]);
    return 0;
}
 
