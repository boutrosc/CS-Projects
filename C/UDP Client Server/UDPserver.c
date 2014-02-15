/***************************************************************
 Author: Charbel Boutros
 File Name: UDPserver.c
 ***************************************************************/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#define _GNU_SOURCE

#define BUFFER_SIZE 256
#define MAX_NUM_LISTENER_ALLOWED 10

/*
 * Identifies if the specified message is well-formed or not.
 *
 * msg - the message to be tested
 *
 * returns a value greater than 0 if the message is well formed and a value less than zero if it is not
 */
int wellFormed(char* msg) {
	int length = strlen(msg);

	if (strcasecmp(msg, "<loadavg/>") == 0) {
		if (length != 10) {
			return -1;
		}
		return 1;
	}
	if (strcasecmp(msg, "<shutdown/>") == 0) {
		if (length != 11) {
			return -1;
		}
		return 1;
	}
	if (strncasecmp(msg, "<echo>", 6) == 0) {
		char* endStr = strstr(msg, "</echo>");
		if (endStr == NULL)
			return -1;
		if (endStr[7] != '\0')
			return -1;
		return 1;
	}

	return -1;
}

/*
 * Determines the load average and writes it as an XML formatted string into the specified string location.
 *
 * resp - memory for a text string to store the XML formatted string specifying load average information
 */
void getLoadAvgResp(char* resp) {
	double resultRuntime[3];

	bzero(resp, BUFFER_SIZE);

	if (getloadavg(resultRuntime, 3) < 0) {
		strcpy(resp, "<error>unable to obtain load average</error>");
		return;
	}

	sprintf(resp, "<replyLoadAvg>%f:%f:%f</replyLoadAvg>", resultRuntime[0],
			resultRuntime[1], resultRuntime[2]);
}

void shutdownServer(char* resp, int sockfd, struct sockaddr_in servaddr) {
	strcpy(resp, "Server shutting down...");
	if (sendto(sockfd, resp, BUFFER_SIZE, 0, (struct sockaddr *) &servaddr,
			sizeof(servaddr)) == -1) {
		perror("Write error");
		return;
	}
	printf("Closing socket and shutting down . . .\n");
	close(sockfd);
	exit(0);
}

/*
 * Generates a response to a request message in accordance with the given protocol in the project documentation.
 * The request message is assumed to be in a correct format.
 *
 * msg - the message that specifies the request from a client
 * resp - memory for a text string to store the response to a request
 */
void getResponse(char* msg, char* resp, int sockfd, struct sockaddr_in servaddr) {
	bzero(resp, BUFFER_SIZE);

	if (strcasecmp(msg, "<loadavg/>") == 0) {
		getLoadAvgResp(resp);
		return;
	}
	if (strcasecmp(msg, "<shutdown/>") == 0) {
		shutdownServer(resp, sockfd, servaddr);
	}

	if (strncasecmp(msg, "<echo>", 6) == 0) {
		int payLoadLength = strlen(msg) - 13;
		strcpy(resp, "<reply>");
		strncpy(&resp[7], &msg[6], payLoadLength);
		strcpy(&resp[7 + payLoadLength], "</reply>");
		return;
	}
}

/*
 * Writes an error message into the specified character array.
 *
 * msg - memory for a text string to store the error message
 */
void createError(char* msg) {
	bzero(msg, BUFFER_SIZE);
	strcpy(msg, "<error>unknown format</error>");
}

/*
 * Prints the host name of the machine to the screen.
 */
void printHostInfo() {
	// getting host name and use dynamic port binding
	char hostname[128];
	gethostname(hostname, 128);
	printf("Hostname: %s\n", hostname);
}

/**
 * Get WAN IP address and print
 */
void getIP() {
	struct ifaddrs * ifAddrStruct = NULL;
	struct ifaddrs * ifa = NULL;
	void * tmpAddrPtr = NULL;
	getifaddrs(&ifAddrStruct);
	for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr->sa_family == AF_INET) {
			tmpAddrPtr = &((struct sockaddr_in *) ifa->ifa_addr)->sin_addr;
			char addressBuffer[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
			if (strcmp(ifa->ifa_name, "eth0") == 0)
				fprintf(stdout, "Address: %s\n", addressBuffer);
		}
	}
	if (ifAddrStruct != NULL)
		freeifaddrs(ifAddrStruct);
}

/*
 * Creates a socket and binds it dynamicaly. Port information of the bound socket is returned.
 */
int createSocket(struct sockaddr_in *servaddr, int port) {
	int sockfd;

	// creating a streaming server socket
	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockfd < 0) {
		return -1;
	}

	// build local address and set port to unknown
	bzero(servaddr, sizeof(struct sockaddr_in *));
	servaddr->sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr->sin_port = htons(port);
	struct sockaddr_in serv_addr = *servaddr;
	// bind dynamically
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
			(socklen_t) sizeof(serv_addr)) == -1) {
		perror("Bind error");
		exit(0);
	}

	// retrieve port information
	struct sockaddr_in boundAddr;
	socklen_t sizeAddr = sizeof(boundAddr);
	getsockname(sockfd, (struct sockaddr *) &boundAddr, &sizeAddr);
	printf("Port: %d\n\n", ntohs(servaddr->sin_port));
	return sockfd;
}

/*
 * Implements the request handler executed within a thread.
 */
void reqHandler(void *value, struct sockaddr_in servaddr) {
	int sockfd = (intptr_t) value;
	socklen_t slen = sizeof(servaddr);
	char msg[BUFFER_SIZE];
	char resp[BUFFER_SIZE];
	bzero(msg, BUFFER_SIZE);
	bzero(resp, BUFFER_SIZE);
	if (recvfrom(sockfd, msg, BUFFER_SIZE - 1, 0, (struct sockaddr*) &servaddr,
			&slen) == -1)
		perror("Receive error");
	printf("Received packet from %s:%d\nRequest: %s\n",
			inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port), msg);
	if (wellFormed(msg) < 0) {
		createError(resp);
	} else {
		getResponse(msg, resp, sockfd, servaddr);
	}
	if (sendto(sockfd, resp, BUFFER_SIZE, 0, (struct sockaddr *) &servaddr,
			sizeof(servaddr)) == -1) {
		perror("Write error");
		return;
	}
	printf("Sent response %s\n\n", resp);
}

/*
 * The main program that starts up the server.
 * No parameters are processed.
 */
int main(int argc, char* argv[]) {
	struct sockaddr_in servaddr;
	int sockfd;
	if (argc != 2) {
		printf("Usage: <port>\n");
		exit(0);
	}
	// provide host name information to the screen
	printHostInfo();
	getIP();

	// creating a streaming server socket
	sockfd = createSocket(&servaddr, atoi(argv[1]));
	if (sockfd < 0) {
		perror("cannot create socket");
		exit(1);
	}

	for (;;) {
		reqHandler((void*) (intptr_t) sockfd, servaddr);
	}
}
