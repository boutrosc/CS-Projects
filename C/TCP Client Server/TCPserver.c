/***************************************************************
 Author: Charbel Boutros
 File Name: TCPserver.c
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXCLIENTS 1

void* parse(void*);
int readHost(struct sockaddr_in*);
void getIP();
int initSocket(struct sockaddr_in, int*);
int serveRequests(int);
int parseEcho(void*, char*, char**);
int replyEcho(void*, char*);
void parseLoadAvg(void*, char**);
int replyLoadAvg(void*);
int error(void*);
int debug;

int main() {
	//turn debug on or off
	debug = 0;
	int listensock = 0;
	struct sockaddr_in servaddr;
	if (readHost(&servaddr) == -1)
		return 0;
	if (initSocket(servaddr, &listensock) == -1)
		return 0;
	if (serveRequests(listensock) == -1)
		return 0;
	return 0;
}

/**
 * Reads host server information
 * @param servaddr - contains host server information
 * @param port - indicates server port to be used
 */
int readHost(struct sockaddr_in *servaddr) {
	char buffer[256], hostname[32];
	struct hostent *hostptr;
	bzero(buffer, 256);
	bzero(hostname, 32);
	gethostname(hostname, 32);
	hostptr = gethostbyname(hostname);
	fprintf(stdout, "Host Name: %s\n", hostptr->h_name);
	memset(servaddr, 0, sizeof(servaddr));
	memset(buffer, 0, sizeof(buffer));
	servaddr->sin_family = AF_INET;
	servaddr->sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr->sin_port = htonl(0);
	getIP();
	return 0;
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

/**
 * Creates and binds socket
 * @param listensockFD - socket connection
 * @param servaddr - contains host server information
 */
int initSocket(struct sockaddr_in servaddr, int *listensock) {
	*listensock = socket(AF_INET, SOCK_STREAM, 0);
	if (*listensock == -1) {
		perror("Socket error");
		return -1;
	}
	if (bind(*listensock, (struct sockaddr*) &servaddr,
			(socklen_t) sizeof(servaddr)) == -1) {
		perror("Port bind error");
		return -1;
	}
	socklen_t size = sizeof(servaddr);
	if (getsockname(*listensock, (struct sockaddr *) &servaddr, &size) == -1) {
		perror("getsockname error");
	}
	fprintf(stdout, "Port: %d\n", ntohs(servaddr.sin_port));
	if (listen(*listensock, MAXCLIENTS) == -1) {
		perror("Socket listen error");
		return -1;
	}
	if (listen(*listensock, MAXCLIENTS) == -1) {
		perror("Socket listen error");
		return -1;
	}
	return 0;
}

int serveRequests(int listensock) {
	pthread_t thread;
	int connsock = 0;
	for (;;) {
		connsock = accept(listensock, NULL, NULL);
		if (connsock < 0) {
			perror("Socket accept error");
			return -1;
		}
		if (pthread_create(&thread, NULL, parse, (void *) &connsock) != 0) {
			perror("Pthread create error");
			return -1;
		} else
			pthread_detach(thread);
	}
	close(listensock);
	return 0;
}
/**
 * Parses client input
 * @param conn - socket connection
 */
void* parse(void* conn) {
	char buffer[256], *temp;
	bzero(buffer, 256);
	int connection = *((int*) conn);
	recv(connection, buffer, sizeof(buffer), 0);
	if (debug)
		fprintf(stdout, "Request: %s", buffer);
	if (strncmp(buffer, "<", 1) != 0)
		error(&connection);
	else if (parseEcho(&connection, buffer, &temp) == -1)
		parseLoadAvg(&connection, &temp);
	pthread_exit(NULL);
	return NULL;
}

/**
 * Parses echo command received by user
 *@param conn - socket connection
 *@param buffer - user input buffer
 */
int parseEcho(void *conn, char *buffer, char **temp) {
	char reply[256];
	bzero(reply, 256);
	int connection = *((int*) conn);
	*temp = strtok(buffer, "<>");
	if (strcmp(*temp, "echo") == 0) {
		*temp = strtok(NULL, "<>");
		if (*temp == NULL)
			error(&connection);
		strcpy(reply, *temp);
		*temp = strtok(NULL, "<> ");
		if (strcmp(reply, "/echo") == 0
				&& (*temp == NULL || strcmp(*temp, "\n") == 0))
			replyEcho(&connection, "");
		if (*temp != NULL && strcmp(*temp, "/echo") == 0) {
			*temp = strtok(NULL, "");
			if (*temp == NULL || strcmp(*temp, "\n") == 0)
				replyEcho(&connection, reply);
			else
				error(&connection);
		} else
			error(&connection);
	} else
		return -1;
	return 0;
}

/**
 * Replies to client's echo command
 * @param conn - socket connection
 * @param reply - message to send to client
 */
int replyEcho(void *conn, char *reply) {
	int connection = *((int*) conn);
	char echoReply[256] = "<reply>";
	strcat(echoReply, reply);
	strcat(echoReply, "</reply>\t\t\t\t");
	if (debug)
		fprintf(stdout, "Response: %s\n", echoReply);
	if (write(connection, echoReply, strlen(echoReply)) == -1) {
		perror("Write error");
		return -1;
	}
	close(connection);
	return 0;
}

/**
 * Parses loadavg command received by user
 *@param conn - socket connection
 *@param buffer - user input buffer
 */
void parseLoadAvg(void *conn, char **temp) {
	int connection = *((int*) conn);
	//char *temp = strtok(buffer, "<>");
	if (strcmp(*temp, "loadavg/") == 0) {
		*temp = strtok(NULL, "");
		if (*temp == NULL || strcmp(*temp, "\n") == 0)
			replyLoadAvg(&connection);
		else
			error(&connection);

	} else
		error(&connection);
}

/**
 * Replies to client's loadavg command
 * @param conn - socket connection
 */
int replyLoadAvg(void *conn) {
	int connection = *((int*) conn);
	char loadAvg[256];
	char echoReply[256];
	bzero(echoReply, 256);
	strcpy(echoReply, "<replyLoadAvg>");
	double reply[3];
	bzero(loadAvg, 256);
	getloadavg(reply, 3);
	sprintf(loadAvg, "%lf:%lf:%lf", reply[0], reply[1], reply[2]);
	strcat(echoReply, loadAvg);
	strcat(echoReply, "</replyLoadAvg>");
	if (debug)
		fprintf(stdout, "Response: %s\n", echoReply);
	if (write(connection, echoReply, strlen(echoReply)) == -1) {
		perror("Write error");
		return -1;
	}
	close(connection);
	return 0;
}

/**
 * Sends error response to client
 * @param conn - socket connection
 */
int error(void *conn) {
	int connection = *((int*) conn);
	char error[256] = "<error>unknown format</error> ";
	if (debug)
		fprintf(stdout, "Response: %s\n", error);
	if (write(connection, error, strlen(error)) == -1)
		return -1;
	close(connection);
	return 0;
}
