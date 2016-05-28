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
#include <errno.h>
#include <msgpack.hpp>
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
	// declare variable
	int sockfd, n;
	char recvline[MAXLINE + 1];
	int child_number = 0;
	struct sockaddr_in server_address;

	//usage detect
	if(argc!=3){
		printf("usage:server_client <IP address>\n");
		return 0;
	}

	// create connect descriptor
	if( (sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0 )
		perror("socket create error");

	//setting server_address
	bzero( &server_address, sizeof(server_address) );
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(atoi(argv[2]));
	if( inet_pton(AF_INET, argv[1], &server_address.sin_addr) <= 0 ){
		printf("Can't identify IP address %s \n", argv[1]);
		return 1;
	}

	if( connect(sockfd, (sockaddr* )(&server_address), sizeof(server_address)) < 0 ){
		perror("connect error");
		return 1;
	}

	// main function
	str_cli(stdin, sockfd);
	return 0;
}