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
#include <time.h>
#include <thread>
#include <pthread.h>
#include "client_function.cpp"
#define MAXLINE 4096
#define BACKLOG 30

void* client_connect(void* info){
    thread_info* new_info = (thread_info* )info;
    int sockfd = new_info -> sockfd;
    std::string addr = new_info -> address;
    int port = new_info -> port;

    int read_size;
    char client_message[200];
    while( (read_size = recv(sockfd, client_message, 2000, 0)) > 0 ){
		client_message[read_size] = '\0';
        printf("%s\n", client_message);
		memset(client_message, 0, 2000);
    }

    if(read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    }else if(read_size == -1){
        perror("recv failed");
    }
    return 0;
}

int new_listen_thread(){
	int listenFD, connectFD;
	srand(time(NULL));
    int port_num = rand()%10000 + 20000;
    std::cout << port_num << '\n';

	pthread_t tid;
	socklen_t addrlen, len;
	sockaddr_in* client_address = new sockaddr_in, server_address;

    //create listen descriptor
	listenFD = socket(AF_INET, SOCK_STREAM, 0);

    //setting server informations
	server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons( port_num );

    // bind socket and descriptor
    if( bind(listenFD, (sockaddr *)&server_address, sizeof(server_address)) < 0){
        printf("bind error");
        return 1;
    }

    // start listen and backlog is the maxium of connection Simultaneous
    if (-1 == listen(listenFD, BACKLOG)) {
        perror("listen");
    }

    len = sizeof(sockaddr_in);
    while( (connectFD = accept(listenFD, (sockaddr*)client_address, &len)) > 0 ){
        char cli_addr[200];
        inet_ntop(AF_INET, &(client_address->sin_addr), cli_addr, INET_ADDRSTRLEN);
        std::string addr(cli_addr);
        thread_info* info = new thread_info(connectFD, addr, client_address->sin_port);
        //printf( "Connect from %s %d\n", cli_addr, client_address->sin_port );
    	if( pthread_create( &tid, NULL, client_connect, (void *)info ) ){
    		printf("Thread create error\n");
    		return 1;
    	}
    }
}

void client(FILE* fp, int sockfd){
	login::Login user;
	while( !identity(sockfd, &user) );

	printf("%sWelcome to Simple Peer to Peer server%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);

	sendFileInfo(sockfd);

	std::thread listenThread(new_listen_thread);

	while(true){
		printf("[K]ill\t\t[L]ogout\t[S]earchInfo\n[D]ownload\t[C]hat\t\t[O]line\n");
		std::string cmd;
		std::cin >> cmd;
		if( cmd == "K" || cmd == "k" ){
			if( delete_account(sockfd, user) )
				break;
		}else if( cmd == "L" || cmd == "l" ){
			logout(sockfd, user);
			break;
		}else if( cmd == "S" || cmd == "s" ){
			search_info(sockfd);
		}else if( cmd == "D" || cmd == "d" ){
			download(sockfd);
		}else if( cmd == "C" || cmd == "c" ){
			chat(sockfd);
		}else if( cmd == "O" || cmd == "o"){
			get_onlien_info(sockfd);
		}else{
			printf("%sInvalid Input !%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
		}
	}

	listenThread.detach();
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
