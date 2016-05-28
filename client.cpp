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
#include <iostream>
#include "GPB/login.pb.cpp"
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#define MAXLINE 4096

void login_to_server(){
	std::string account;
	char passwd[20];
	printf("Account:");


}

void regist_to_server(){
	std::string account;
	std::string password;
	int passwd_count = 0;
	printf("Account:");
	std::cin >> account;
	printf("Password:");
	std::cin >> password;
}

void identity(){
	printf("[L]ogin\t[R]egist\n");
	std::string command;
	while( std::cin >> command ){
		if( command == "L" || command == "l" ){
			login_to_server();
			break;
		}else if(command == "R" || command == "r"){
			regist_to_server();
			break;
		}else{
			printf("Cannot identify your input\n");
		}
	}
}

google::protobuf::uint32 readHdr(char *buf){
	google::protobuf::uint32 size;
	google::protobuf::io::ArrayInputStream ais(buf,4);
	google::protobuf::io::CodedInputStream coded_input(&ais);
	coded_input.ReadVarint32(&size); //Decode the HDR and get the size
	//cout<<"size of payload is "<<size<<endl;
	return size;
}

void readBody(int csock,google::protobuf::uint32 siz){
	int byteCount;
	action::Login login;
	char buffer [siz+4];
  	if( ( byteCount = recv(csock, (void *)buffer, 4+siz, MSG_WAITALL) )== -1 ){
        fprintf(stderr, "Error receiving data %d\n", errno);
    }
    google::protobuf::io::ArrayInputStream ais(buffer,siz+4);
    google::protobuf::io::CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&siz);
    google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(siz);
    login.ParseFromCodedStream(&coded_input);
    coded_input.PopLimit(msgLimit);
    std::cout << login.DebugString();
}

void client(FILE* fp, int sockfd){
	identity();
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
	client(stdin, sockfd);
	return 0;
}