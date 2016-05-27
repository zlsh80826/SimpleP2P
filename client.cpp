#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define MAXLINE 4096
using namespace std;

void str_cli(FILE* fp, int sockfd){
	char sendline[MAXLINE], recvline[MAXLINE];

	read(sockfd, recvline, MAXLINE);
	fputs(recvline, stdout);

	while( fgets(sendline, MAXLINE, fp) != NULL ){
		write(sockfd, sendline, strlen(sendline));
		if(read(sockfd, recvline, MAXLINE)==0){
			printf("str_cli: server terminated prematurely");
			return;
		}
		fputs(recvline, stdout);
	}
}

int main(int argc, char** argv){
	int sockfd, n;
	char recvline[MAXLINE + 1];
	int child_number = 0;
	struct sockaddr_in server_address;

	if(argc!=3){
		printf("usage:server_client <IP address>\n");
		return 0;
	}

	if( (sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("socket create error\n");

	bzero(&server_address, sizeof(server_address));
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(atoi(argv[2]));
	if(inet_pton(AF_INET, argv[1], &server_address.sin_addr) <= 0)
		printf("inet_pton error for %s\n", argv[1]);

	if(connect(sockfd, (sockaddr* )(&server_address), sizeof(server_address)) < 0)
			printf("connect error\n");
	str_cli(stdin, sockfd);
	/*while( (n=read(sockfd, recvline, MAXLINE) ) ){
		recvline[n]=0;
		if(fputs(recvline, stdout) == EOF)
			printf("fputs error");
	}
	if( n<0 )
		printf("read error");*/
	return 0;
}