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
#include "client_function.cpp"
#define MAXLINE 4096

void client(FILE* fp, int sockfd){
	while( !identity(sockfd) );

	printf("%sWelcome to Simple Peer to Peer server%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);

	while(true){
		printf("[D]elete[A]ccount\t[L]ogout\t[S]earchInfo\n[D]ownload\t[C]hat\n");
		std::string cmd;
		std::cin >> cmd;
		if( cmd == "DA" || cmd == "da" ){
			delete_account(sockfd);
		}else if( cmd == "L" || cmd == "l" ){
			printf("%sGood Bye!%s\n", ANSI_COLOR_YELLOW, ANSI_COLOR_RESET);
			break;
		}else if( cmd == "S" || cmd == "s" ){
			search_info(sockfd);
		}else if( cmd == "D" || cmd == "d" ){
			download(sockfd);
		}else if( cmd == "C" || cmd == "c" ){
			chat(sockfd);
		}else{
			printf("%sInvalid Input !%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
		}
	}

	/*
	//test block
	int count;
	char buffer[4];
	count = recv(sockfd, buffer, 4, MSG_PEEK);
	if(count == -1)
		printf("error\n");
	else{
		readBody(sockfd, readHdr(buffer));
	}
	//test block

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
	}*/
}

int main(int argc, char** argv){
	// declare variable
	int sockfd, n;
	char recvline[MAXLINE + 1];
	int child_number = 0;
	struct sockaddr_in server_address;

	//usage detect
	if( argc!=3 ){
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
	client(stdin, sockfd);
	return 0;
}
