#include <stdio.h>
#include "CSRSocket.c"
#define BUFFER 256

DWORD WINAPI server(LPVOID param){
	int port = (int) param;
	char msg[BUFFER] = "";
	
	while(strcmp(msg, "exit") != 0){
		receber(port, msg);
		printf("%s\n",msg);
 }
}
DWORD WINAPI client(LPVOID param){
	int port = (int) param;
	char msg[BUFFER] = "";
	SOCKET sock;
	
	while(strcmp(msg, "exit")){
		fgets(msg, BUFFER, stdin);
		while(conectar(&sock, "127.0.0.1", port) < 0);
		enviar(sock, msg);
	}
}

int main(int argc, char *argv[]){
	DWORD dwThreadID;
	HANDLE thServer, thClient;
	int serverPort = 8221, clientPort = 8222;
	
	if(strcmp(argv[1], "2")){
		serverPort = 8222;
		clientPort = 8221;
	}
	thServer = (HANDLE) CreateThread(NULL, 0, server, (int *) serverPort, CREATE_SUSPENDED, &dwThreadID);
	thClient = (HANDLE) CreateThread(NULL, 0, client, (int *) clientPort, CREATE_SUSPENDED, &dwThreadID);

	// run threads
	ResumeThread(thServer);
	ResumeThread(thClient);
	
	// wait for threads to finish
	WaitForSingleObject(thServer, INFINITE);
	WaitForSingleObject(thClient, INFINITE);
	
	CloseHandle(thServer);
	CloseHandle(thClient);
	return 0;
	
}
