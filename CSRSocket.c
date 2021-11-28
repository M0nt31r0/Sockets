#include <winsock.h>

// Helper macro for displaying errors
#define PRINTERROR(s)	\
		fprintf(stderr,"\n%: %d\n", s, WSAGetLastError())

int conectar(SOCKET* psock, char IP[15], int porta)
{
    struct sockaddr_in alvo;
    WSADATA wsaData;
    
    // The WSAStartup function initiates use of the Winsock DLL by a process.
    // http://msdn.microsoft.com/en-us/library/ms742213%28VS.85%29.aspx
    WSAStartup(MAKEWORD(1, 1), &wsaData);
    
    // The socket function creates a socket that is bound to a specific transport service provider.
    // http://msdn.microsoft.com/en-us/library/ms740506%28VS.85%29.aspx
    if ((*psock=socket(AF_INET, SOCK_STREAM, 0))<0){
       perror("Erro ao inicializar o socket!");
       exit(1);
    }
    
    alvo.sin_family = AF_INET; // AF_INET (2) -  Internet Protocol 4 (IPv4).
    alvo.sin_port = htons(porta);
    alvo.sin_addr.s_addr = inet_addr(IP); 
    memset(&(alvo.sin_zero), '/0', 8);
    
    // The connect function establishes a connection to a specified socket.
    // http://msdn.microsoft.com/en-us/library/ms737625%28VS.85%29.aspx
    return connect(*psock, (struct sockaddr *)&alvo, sizeof(struct sockaddr));   
}

int enviar(SOCKET psock, char mensagem[])
{
    // The send function sends data on a connected socket.
    // http://msdn.microsoft.com/en-us/library/ms740149%28VS.85%29.aspx
    return send(psock, mensagem, sizeof(char)*strlen(mensagem), MSG_DONTROUTE);
}



void StreamServer(short nPort, char *retorno)
{
	//
	// Create a TCP/IP stream socket to "listen" with
	//
	SOCKET	listenSocket;

	listenSocket = socket(AF_INET,			// Address family
						  SOCK_STREAM,		// Socket type
						  IPPROTO_TCP);		// Protocol
	if (listenSocket == INVALID_SOCKET)
	{
		PRINTERROR("socket()");
		return;
	}


	//
	// Fill in the address structure
	//
	SOCKADDR_IN saServer;		

	saServer.sin_family = AF_INET;
	saServer.sin_addr.s_addr = INADDR_ANY;	// Let WinSock supply address
	saServer.sin_port = htons(nPort);		// Use port from command line

	//
	// bind the name to the socket
	//
	int nRet;

	nRet = bind(listenSocket,	// Socket 
		(LPSOCKADDR)&saServer,	// Our address
		sizeof(struct sockaddr));// Size of address structure
	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("bind()");
		closesocket(listenSocket);
		return;
	}

	//
	// This isn't normally done or required, but in this 
	// example we're printing out where the server is waiting
	// so that you can connect the example client.
	//
	int nLen;
	nLen = sizeof(SOCKADDR);
	char szBuf[256];

	nRet = gethostname(szBuf, sizeof(szBuf));
	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("gethostname()");
		closesocket(listenSocket);
		return;
	}

	
	nRet = listen(listenSocket,	// Bound socket
		SOMAXCONN);	// Number of connection request queue
	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("listen()");
		closesocket(listenSocket);
		return;
	}

	//
	// Wait for an incoming request
	//
	SOCKET	remoteSocket;

	
	remoteSocket = accept(listenSocket,  // Listening socket
		NULL,	// Optional client address
		NULL);
	if (remoteSocket == INVALID_SOCKET)
	{
		PRINTERROR("accept()");
		closesocket(listenSocket);
		return;
	}

	//
	// We're connected to a client
	// New socket descriptor returned already
	// has clients address

	//
	// Receive data from the client
	//
	memset(szBuf, 0, sizeof(szBuf));
	nRet = recv(remoteSocket,					// Connected client
				szBuf,							// Receive buffer
				sizeof(szBuf),					// Length of buffer
				0);								// Flags
	if (nRet == INVALID_SOCKET)
	{
		PRINTERROR("recv()");
		closesocket(listenSocket);
		closesocket(remoteSocket);
		return;
	}

	//
	// Display received data
	//
	szBuf[nRet]=0;

    // copia os dados recebidos para a variável passada
    strcpy(retorno, szBuf);

	//
	// Send data back to the client
	//
	//strcpy(szBuf, "From the Server");
	nRet = send(remoteSocket,				// Connected socket
				szBuf,						// Data buffer
				strlen(szBuf),				// Lenght of data
				0);							// Flags

	//
	// Close BOTH sockets before exiting
	//
	closesocket(remoteSocket);
    closesocket(listenSocket);
     
	return;
}


void receber(int porta, char * retorno)
{
	WORD wVersionRequested = MAKEWORD(1,1);
	WSADATA wsaData;
	int nRet;
	short nPort;
    char msg[256]="";

	nPort = porta;

	//
	// Initialize WinSock and check version
	//
	nRet = WSAStartup(wVersionRequested, &wsaData);
	if (wsaData.wVersion != wVersionRequested)
	{	
		fprintf(stderr,"\n Wrong version\n");
		return;
	}

	//
	// Do the stuff a stream server does
	//
	StreamServer(nPort, retorno);
		
	//
	// Release WinSock
	//
	WSACleanup();
	
	return;
}

////////////////////////////////////////////////////////////

