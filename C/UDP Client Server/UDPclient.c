/***************************************************************
 Author: Charbel Boutros
 File Name: UDPclient.c
 ***************************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "UDPclient.h"

/*
 * Creates a datagram socket and connects to a server.
 *
 * serverName - the ip address or hostname of the server given as a string
 * serverPort - the port number of the server
 * dest       - the server's address information; the structure will be initialized with information
 *              on the server (like port, address, and family) in this function call
 *
 * return value - the socket identifier or a negative number indicating the error if a connection could not be established
 */
int createSocket(char * serverName, int serverPort, struct sockaddr_in * dest) {
	int sockfd = 0;
	bzero(dest, (size_t) sizeof(dest));
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		perror("Socket error");
		return -1;
	}
	bzero(dest, sizeof(struct sockaddr_in));
	dest->sin_family = AF_INET;
	dest->sin_port = htons(serverPort);
	if (inet_aton(serverName, &dest->sin_addr) <= 0) {
		perror("inet_aton error");
		return -1;
	}
	return sockfd;
}

/*
 * Sends a request for service to the server. This is an asynchronous call to the server,
 * so do not wait for a reply in this function.
 *
 * sockFD  - the socket identifier
 * request - the request to be sent encoded as a string
 * dest    - the server's address information
 *
 * return   - 0, if no error; otherwise, a negative number indicating the error
 */
int sendRequest(int sockFD, char * request, struct sockaddr_in * dest1) {
	char buffer[256];
	bzero(buffer, 256);
	strcpy(buffer, request);
	struct sockaddr_in dest = *dest1;
	if (sendto(sockFD, buffer, sizeof(buffer), 0, (struct sockaddr*) &dest,
			sizeof(dest)) == -1)
		perror("Send error");
	return 0;
}

/*
 * Receives the server's response formatted as an XML text string.
 *
 * sockfd    - the socket identifier
 * response  - the server's response as an XML formatted string to be filled in by this function into the specified string array
 *
 * return   - 0, if no error; otherwise, a negative number indicating the error
 */
int receiveResponse(int sockFD, char *response) {
	char buffer[256];
	bzero(buffer, 256);
	recv(sockFD, buffer, 255, 0);
	strcpy(response, buffer);
	return 0;
}

/*
 * Prints the response to the screen in a formatted way.
 *
 * response - the server's response as an XML formatted string
 *
 */
void printResponse(char *response) {
	printf("%s\n", response);
}

/*
 * Closes the specified socket
 *
 * sockFD - the ID of the socket to be closed
 *
 * return - 0, if no error; otherwise, a negative number indicating the error
 */
int closeSocket(int sockFD) {
	if (close(sockFD) == -1) {
		perror("Closing socket error");
		return -1;
	}
	return 0;
}
