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

void into_orcish(char* src) {
	int len = strlen(src);
	if (len > 5) {
		src[0] = 'W';
		for (int i = 1; i < len - 4; ++i){
			src[i] = 'A';
		}
		src[len - 4] = 'G';
		src[len - 3] = 'H';
		src[len - 2] = '!';
		src[len - 1] = '\n';
	} else {
		memset(src, 0, BUF_SIZE);
		strcpy(src, "Unknown pattern");
	}		 
}

int main(int argc, char** argv) {
	uint16_t host_port = htons(PORT);
	char buf[BUF_SIZE];


	int sockd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockd == -1) {
		fprintf(stderr, "socket error");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in host_addr;
	struct sockaddr_in peer_addr;
	memset(&host_addr, 0, sizeof(host_addr));
	
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = host_port;
	inet_aton(IP_ADDRESS, &host_addr.sin_addr);


	if (bind(sockd, (struct sockaddr*)&host_addr, sizeof(host_addr)) == -1) {
		fprintf(stderr, "bind error");
		exit(EXIT_FAILURE);
	}
	
	while (1) {
		memset(&buf, 0, BUF_SIZE * sizeof(char));
		socklen_t len = sizeof(peer_addr);
		int l = recvfrom(sockd, buf, BUF_SIZE, 0, (struct sockaddr*)&peer_addr, &len);
		buf[l - 4] = '\0';
		fprintf(stderr,"recv from: %s %d\n", inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port));
		
		into_orcish(buf);

		if (sendto(sockd, buf, BUF_SIZE, 0, (struct sockaddr*)&peer_addr, len) != l)
			fprintf(stderr, "error sending mess");
	}

	close(sockd);
	return 0;	
}