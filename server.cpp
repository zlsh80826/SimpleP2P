#include <pthread.h>
#include <sys/socket.h>
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
#include "login.pb.h"
#include "action.pb.h"
#include "regist.pb.h"
#include "gdb_handle.cpp"
#define BACKLOG 30

void login_check(int sockfd){
    int count;
    char bufferFST[4];
    count = recv(sockfd, bufferFST, 4, MSG_PEEK);
    if(count == -1)
        perror("Recv with error");

    google::protobuf::uint32 size = readHdr(bufferFST);
    int byteCount;
    login::Login login;
    char buffer[size + HDR_SIZE];
    if( ( byteCount = recv(sockfd, (void *)buffer, size + HDR_SIZE, MSG_WAITALL) )== -1 ){
        perror("Error recviving data");
    }
    google::protobuf::io::ArrayInputStream ais(buffer, size + HDR_SIZE);
    google::protobuf::io::CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&size);
    google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(size);
    login.ParseFromCodedStream(&coded_input);
    coded_input.PopLimit(msgLimit);
    std::cout << login.DebugString();
}

void regist_check(int sockfd){

}

void* client_connect(void *);

int main(int argc, char** args){

    //argc error detect
    if(argc != 2){
        printf("Usage: ./server <port_num> \n");
        return 1;
    }

    //arguments declare
	int listenFD, connectFD;
    int port_num = atoi(args[1]);
	pthread_t tid;
	socklen_t addrlen, len;
	sockaddr_in* client_address, server_address;

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
    listen(listenFD, BACKLOG);

    len = sizeof(sockaddr_in);
    while( connectFD = accept(listenFD, (sockaddr*)client_address, &len) ){
        char cli_addr[200];
        inet_ntop(AF_INET, &(client_address->sin_addr), cli_addr, INET_ADDRSTRLEN);
        printf( "Connect from %s %d\n", cli_addr, client_address->sin_port );
    	if( pthread_create(&tid, NULL, client_connect, (void *)&connectFD ) ){
    		printf("Thread create error\n");
    		return 1;
    	}
    }

    if ( connectFD < 0 ){
        perror("accept failed");
        return 1;
    }



    return 0;

}

void* client_connect(void* connectFD){
    int sockfd = *(int*)connectFD;

    int read_size;
    char client_message[2000];
    char welcome_message[200];
    strcpy(welcome_message, "Welcome to simple P2P server !\n");

    write(sockfd, welcome_message, strlen(welcome_message));
	//test block

	login::Login login;
	login.set_id("testID");
	login.set_passwd("testPasswd");
	int pkg_size = login.ByteSize() + 4;
	char* pkt = new char[pkg_size];
	google::protobuf::io::ArrayOutputStream aos(pkt, pkg_size);
	google::protobuf::io::CodedOutputStream* coded_output = new google::protobuf::io::CodedOutputStream(&aos);
	coded_output -> WriteVarint32(login.ByteSize());
	login.SerializeToCodedStream(coded_output);

	write(sockfd, pkt, pkg_size);
	//test block

    while( true ){
        int count;
        char buffer[4];
        count = recv(sockfd, buffer, 4, MSG_PEEK);
        if(count == -1)
            perror("Recv with error");
        else{
            ACTION request;
            request = readAction(sockfd, readHdr(buffer));
            if (request == LOGIN) {
                login_check(sockfd);
            } else if(request == REGIST) {
                regist_check(sockfd);
            }
        }
    }

    /*while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 ){
		client_message[read_size] = '\0';
        write(sock , client_message , strlen(client_message));
		memset(client_message, 0, 2000);
    }

    if(read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    }else if(read_size == -1){
        perror("recv failed");
    }*/

    return 0;
}
