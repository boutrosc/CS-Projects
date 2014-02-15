/***************************************************************
 Student Name: Charbel Boutros, Blake Holtzen
 File Name: UDPmain.c
 Project 2
 ***************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include "UDPclient.h"

/*
 * A test program to start a client and connect it to a specified server.
 * Usage: client <hostname> <portnum>
 *    client is this client program
 *    <hostname> IP address or name of a host that runs the server
 *    <portnum> the numeric port number on which the server listens
 */
int main(int argc, char** argv)
{
	int                sockfd;
	struct sockaddr_in servaddr;
	char               response[256];
	char               message[256];

	if (argc != 3) {
		fprintf (stderr, "Usage: client <hostname> <portnum>\n");
		exit (1);
	}

	// parse input parameter for port information
	int portNum = atoi (argv[2]);

	// create a streaming socket
	sockfd = createSocket(argv[1], portNum, &servaddr);
	if (sockfd < 0) {
		exit (1);
	}
	printf ("Enter a message: ");
	fgets (message, 256, stdin);
	// replace new line with null character
	message[strlen(message)-1] = '\0';

	// send request to server
	//if (sendRequest (sockfd, "<echo>Hello, World!</echo>", &servaddr) < 0) {
	if (sendRequest (sockfd, message, &servaddr) < 0) {
		close (sockfd);
		exit (1);
	}

	if (receiveResponse(sockfd, response) < 0) {
		close (sockfd);
		exit (1);
	}
	closeSocket (sockfd);

	// display response from server
	printResponse(response);

	exit(0);
}

