/*
 ============================================================================
 Name        : server.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#if defined WIN32
#include <winsock.h>
#else
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#define closesocket close
#endif

#include <stdio.h>
#include "header.h"

///***********************
/// DEFINE FUNCTION
///***********************

void clearwinsock() {
#if defined WIN32
	WSACleanup(); /// IT CANCELS THE IMPLEMENTATION OF WINDOWS SOCKET AND FREES THE RESOURCES ALLOCATED BY THE APPLICATION OR BY THE DDL FILE
#endif
}

int add(int a, int b) {
	return a + b;
}

int mult(int a, int b) {
	return a * b;
}

int sub(int a, int b) {
	return a - b;
}

int division(int a, int b) {
	return a / b;
}

SOCKET accept_client(int socket_server, SOCKET socket_client, int len_client) {
	socket_client = accept(socket_server, (struct sockaddr*) &cad, &len_client);
	if (socket_client == INVALID_SOCKET) {
		wprintf(L"L'accettazione e' fallita con errore : %ld\n",
				WSAGetLastError());
		closesocket(socket_server);  // CHIUDUSRA DELLA CONNESSIONE
		clearwinsock();
		return 1;
	} else {
		printf("Connection established with %s:%d\n", inet_ntoa(cad.sin_addr),
				ntohs(cad.sin_port));
		return socket_client;

	}
}

int main(int argc, char *argv[]) {

	///***********************
	/// INSTANCE VARIABLES
	///***********************

	int iResult = 0; /// VARIABLE USED TO CHECK THE RETURN VALUES OF THE FUNCTIONS
	int socket_server; /// CONTAINS THE NETWORK SOCKET DESCRIPTOR
	SOCKET socket_client; /// CREATION OF A SOCKET TO ACCEPT INCOMING REQUESTS

	sad.sin_family = AF_INET;
	sad.sin_addr.s_addr = inet_addr(ADDRESS_CLIENT_SERVER);
	sad.sin_port = htons(PORT_WELCOME_SERVER);

#if defined WIN32
	WSADATA wsa_data; /// STRUCTURE THAT CONTAINS ALL THE IMPLEMENTATION INFORMATION OF WINDOWS SOCKET
	iResult = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (iResult != NO_ERROR) {
		wprintf(L"WSAStartup() failed with error: %d\n", iResult);
		return 0;
	}
#endif

	/// SOCKET CREATION
	socket_server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socket_server == INVALID_SOCKET) { /// CHECK IF THE OUTCOME OF THE CONNECTION WAS SUCCESSFUL
		wprintf(L"the function socket is failed with error: %u\n",
				WSAGetLastError());
		closesocket(socket_server);
		clearwinsock();
		return 1;
	}

	iResult = bind(socket_server, (struct sockaddr*) &sad, sizeof(sad));
	if (iResult == SOCKET_ERROR) {
		wprintf(L"the function bind is failed with error: %u\n",
				WSAGetLastError());
		closesocket(socket_server);
		clearwinsock();
		return 1;
	}

	/// CREATE A LISTENING CONNECTION ON THE SERVER.
	if (listen(socket_server, QLEN) == SOCKET_ERROR) {
		wprintf(L"the function listen is failed with error: %d\n",
				WSAGetLastError());
		closesocket(socket_server);
		clearwinsock();
		return 1;
	}
	for (;;) {
		accept_client(socket_server, socket_client, sizeof(cad));
	}

	///***********************
	/// CLOSE CONNECTION
	///***********************

	closesocket(socket_server); // close socket connection
	clearwinsock();
	return 0;
} // main end
