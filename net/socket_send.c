#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#define SYSCALL_ERROR(ret, call, ...)\
	ret = call(__VA_ARGS__);\
	if(ret < 0){\
		fprintf(stderr, "%s error at line %d,\nError: %s", #call, __LINE__, strerror(errno));\
		exit(-1);\
	}

int main(int argc, char *argv[]){

	int sockfd = 0;
	struct sockaddr_in serv_addr; 
	if(argc < 2){
		printf("%s <ip> <port>\n", argv[0]);
		exit(0);
	}
	char buf[1025];
	int ret;
	int len;

	SYSCALL_ERROR(sockfd, socket, AF_INET, SOCK_STREAM, IPPROTO_IP);

	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(buf, '0', sizeof(buf));

	char ch;
	int i = 0;
	while((ch = getchar()) != '\n'){
		buf[i++] = ch;
	}
	buf[i++] = ch;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));

	if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<0){
		printf("\n inet_pton error occured\n");
		return 1;
	} 

	SYSCALL_ERROR(ret, connect, sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	SYSCALL_ERROR(len, sendto, sockfd, buf, strlen(buf), 0, NULL, 0);

	close(sockfd);

	return 0;
}

