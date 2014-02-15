/***************************************************************
 Author: Charbel Boutros
 File Name: TCPmain.c
 Project 1
 ***************************************************************/

#include "TCPclient.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#define MAXBYTES 256

void handleInput(int);
void inputStream(char *);

int main(int argc, char* argv[]) {
	handleInput(argc);
	struct sockaddr_in *dest = malloc(sizeof(struct sockaddr_in)); //FREE
	char userIn[MAXBYTES], response[MAXBYTES];
	int socket = 0;
	while (1) {
		if ((socket = createSocket(argv[1], atoi(argv[2]), dest)) == -1)
			return 0;
		bzero(userIn, MAXBYTES);
		inputStream(userIn);
		if (strcmp(userIn, "exit\n") == 0)
			return 0;
		if (sendRequest(socket, userIn, dest) == -1)
			return 0;
		if (receiveResponse(socket, response) == -1)
			return 0;
		printResponse(response);
	}
	closeSocket(socket);
	free(dest);
	return 0;

}

/**
 * Handles command arguements
 * @param argc - arguement count
 */
void handleInput(int argc) {
	if (argc != 3) {
		fprintf(stderr, "Invalid Arguements\n");
		fprintf(stderr, "Usage: <hostname> <portnum>\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * Handles user input stream
 * @param userin - user's input
 */
void inputStream(char *userIn) {
	printf("$ ");
	if (strcmp(fgets(userIn, MAXBYTES, stdin), "EOF"))
		return;
}
