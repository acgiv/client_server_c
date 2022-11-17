/*
 ============================================================================
 Name        : client.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

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

void clearwinsock() {
#if defined WIN32
	WSACleanup(); /// IT CANCELS THE IMPLEMENTATION OF WINDOWS SOCKET AND FREES THE RESOURCES ALLOCATED BY THE APPLICATION OR BY THE DDL FILE
#endif
}

msgStruct user_data_entry(msgStruct message, int client) {
	printf("Please enter the numbers and math operators in this format; 'operators first_number seconds_ numbers'. \n");
	char c;
	scanf("%c", &c);
	printf("%c", c);
	message.operation = c;
	if (message.operation == '=') {
		return message;
	}
	scanf(" %ld %ld", &message.first_number, &message.second_number);
	fflush(stdin);
	return message;
}

void send_message(int socket_client, msgStruct message) {
	int iResult = send(socket_client, (char*) &message, sizeof(message), 0);
	if (iResult == SOCKET_ERROR) {
		wprintf(L"send message falied with error: %d\n", WSAGetLastError());
		iResult = closesocket(socket_client);
		if (iResult == SOCKET_ERROR)
			wprintf(L"something went wrong while closing the server, error code : %ld\n",
					WSAGetLastError());
		clearwinsock();
		exit(1);
	}
}


boolean receive_message(SOCKET socket_client, msgStruct message) {
	boolean result = FALSE;
	int iResult = recv(socket_client, (char*) &message, sizeof(message), 0);
	if (iResult > 0) {
		printf("%.2lf\n", message.result);
	} else if (iResult == 0)
		closesocket(socket_client);
	else
		printf("recv failed: %d\n", WSAGetLastError());
	return result;
}

int main(int argc, char *argv[]) {

	///***********************
	/// INSTANCE VARIABLES
	///***********************

	int iResult = 0; /// VARIABLE USED TO CHECK THE RETURN VALUES OF THE FUNCTIONS
	int socket_client; /// CONTAINS THE NETWORK SOCKET DESCRIPTOR
	cad.sin_family = AF_INET;
	cad.sin_addr.s_addr = inet_addr(ADDRESS_CLIENT_SERVER);
	cad.sin_port = htons(PORT_WELCOME_SERVER);

#if defined WIN32
	WSADATA wsa_data; /// STRUCTURE THAT CONTAINS ALL THE IMPLEMENTATION INFORMATION OF WINDOWS SOCKET
	iResult = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (iResult != NO_ERROR) {
		wprintf(L"WSAStartup() failed with error: %d\n", iResult);
		return 0;
	}
#endif

	/// SOCKET CREATION
	socket_client = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socket_client == INVALID_SOCKET) { /// CHECK IF THE OUTCOME OF THE CONNECTION WAS SUCCESSFUL
		wprintf(L"the function socket is failed with error: %u\n",
				WSAGetLastError());
		iResult = closesocket(socket_client);
		if (iResult == SOCKET_ERROR)
			wprintf(L"something went wrong while closing the server, error code : %ld\n",
					WSAGetLastError());
		clearwinsock();
		return 1;
	}

	/// CREATE A CONNECTION WITH THE SERVER.
	iResult = connect(socket_client, (struct sockaddr*) &cad, sizeof(cad));
	if (iResult == SOCKET_ERROR) {
		wprintf(L"the function connect is failed with error: %ld\n",
				WSAGetLastError());
		iResult = closesocket(socket_client);
		if (iResult == SOCKET_ERROR)
			wprintf(
					L"the function closesocket connect is failed with error: %ld\n",
					WSAGetLastError());
		clearwinsock();
		return 1;
	}
	msgStruct message;
	for (;;) {

		///*************************
		/// USER DATA ENTRY
		///*************************

		message = user_data_entry(message, socket_client);
		///*************************
		/// SEND MESSAGES TO THE SERVER
		///*************************
		send_message(socket_client, message);
		if (message.operation == '=') {
			fflush(stdin);
			int iResult = closesocket(socket_client);
			if (iResult == SOCKET_ERROR)
				wprintf(L"close function falied, with error: %ld\n",
						WSAGetLastError());
			clearwinsock();
			return 1;
		}
		///*************************
		/// TURNING OFF THE SEND OPERATION
		///*************************
		//disconnection_operation(socket_client, SEND_OPERATION);
		receive_message(socket_client, message);
	}
	iResult = closesocket(socket_client);
	if (iResult == SOCKET_ERROR)
		wprintf(L"close function falied, with error: %ld\n", WSAGetLastError());
	clearwinsock();
	return 0;
} // main end
