#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "orcish.h"

#define BUF_SIZE 1024
#define IP_ADDRESS "127.0.0.1"
#define PORT 2007
int main(int argc, char** argv) {
	uint16_t host_port = htons(PORT);
	char buf[BUF_SIZE];

	int sockd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockd == -1) {
		fprintf(stderr, "socket error");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in host_addr;
	struct sockaddr_in peer_addr;
	int peer_addr_size = sizeof(peer_addr);
	memset(&host_addr, 0, sizeof(host_addr));
	
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = host_port;
	inet_aton(IP_ADDRESS, &host_addr.sin_addr);


	if (bind(sockd, (struct sockaddr*)&host_addr, sizeof(host_addr)) == -1) {
		fprintf(stderr, "bind error");
		exit(EXIT_FAILURE);
	}

	if (listen(sockd, 1) == -1) {
		fprintf(stderr, "listen error");
		exit(EXIT_FAILURE);
	}

	int connection = accept(sockd, (struct sockaddr*) &peer_addr, (socklen_t*)&peer_addr_size);
	if (connection == -1 ) {
		fprintf(stderr, "connection error");
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "%s %d\n", inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port)); 
	while (1) {
		memset(&buf, 0, BUF_SIZE * sizeof(char));
		recv(connection, buf, BUF_SIZE, 0);

		if (strcmp(buf, "exit\n") == 0) {
			break;
		}
		into_orcish(buf);
		send(connection, buf, BUF_SIZE, 0);
	}

	shutdown(sockd, SHUT_RDWR);

	return 0;
}