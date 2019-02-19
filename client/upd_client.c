#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024
#define IP_ADDRESS "127.0.0.1"
#define PORT 2007

int main() {
	uint16_t host_port = htons(PORT);
	char buf[BUF_SIZE];

	int sockd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockd == -1) {
		fprintf(stderr, "socket error");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in host_addr;
	memset(&host_addr, 0, sizeof(host_addr));
	
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = host_port;
	inet_aton(IP_ADDRESS, &host_addr.sin_addr);

	while (1) {
		memset(&buf, 0, BUF_SIZE * sizeof(char));
		fgets((void*)buf, BUF_SIZE, stdin);
		int len = sizeof(host_addr);
		sendto(sockd, buf, BUF_SIZE, 0, (struct sockaddr*)&host_addr, len);
		recvfrom(sockd, buf, BUF_SIZE, 0, (struct sockaddr*)&host_addr, &len);
		printf("%s", buf);
	}
	return 0;
}