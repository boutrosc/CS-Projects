/***************************************************************
 Author: Charbel Boutros
 File Name: TCPclient.c
 ***************************************************************/

#include "TCPclient.h"

/*
 * Creates a streaming socket and connects to a server.
 *
 * serverName - the ip address or hostname of the server given as a string
 * port       - the port number of the server
 * dest       - the server's address information; the structure should be created with information
 *              on the server (like port, address, and family) in this function call
 *
 * return value - the socket identifier or a negative number indicating the error if a connection could not be established
 */
int createSocket(char * serverName, int port, struct sockaddr_in * dest) {
	int sockfd = 0;
	bzero(dest, (size_t) sizeof(dest));
	struct sockaddr_in destL;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket error");
		return -1;
	}
	dest->sin_family = AF_INET;
	dest->sin_port = htons(port);
	if (inet_pton(AF_INET, serverName, &dest->sin_addr) <= 0) {
		perror("inet_pton error");
		return -1;
	}
	destL = *dest;
	if (connect(sockfd, (struct sockaddr *) &destL, sizeof(destL)) < 0) {
		perror("Socket connection error");
		return -1;
	}
	return sockfd;
}

/*
 * Sends a request for service to the server. This is an asynchronous call to the server,
 * so do not wait for a reply in this function.
 *
 * sock    - the socket identifier
 * request - the request to be sent encoded as a string
 * dest    - the server's address information
 *
 * return   - 0, if no error; otherwise, a negative number indicating the error
 */
int sendRequest(int sock, char * request, struct sockaddr_in * dest) {
	int sendlen = strlen(request);
	if (sendto(sock, request, (size_t) sendlen, 0, (struct sockaddr *) &dest,
			(socklen_t) sizeof(dest)) == -1) {
		perror("Send error");
		return -1;
	}
	return 0;
}

/*
 * Receives the server's response formatted as an XML text string.
 *
 * sock     - the socket identifier
 * response - the server's response as an XML formatted string to be filled in by this function;
 *            memory is allocated for storing response
 *
 * return   - 0, if no error; otherwise, a negative number indicating the error
 */
int receiveResponse(int sock, char * response) {
	int n = 0;
	char token[256];
	bzero(response, 256);
	while ((n = read(sock, token, sizeof(token))) > 0) {
		if (n == -1) {
			perror("Receive error");
			return -1;
		} else if (n == 0) return 0;
		strcat(response, token);
	}
	return 0;
}

/*
 * Prints the response to the screen in a formatted way.
 *
 * response - the server's response as an XML formatted string
 *
 */
void printResponse(char* response) {
	fprintf(stdout, "%s\n", response);
}

/*
 * Closes the specified socket
 *
 * sock - the ID of the socket to be closed
 *
 * return - 0, if no error; otherwise, a negative number indicating the error
 */
int closeSocket(int sock) {
	if (close(sock) == -1){
		perror("Closing socket error");
		return -1;
	}
	return 0;
}
