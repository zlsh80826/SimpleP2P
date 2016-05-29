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
#include <fstream>
#include "gdb_handle.cpp"
#include "define.h"
#include <set>
#define BACKLOG 30

Data::LoginData loginData;
std::set<std::string> file_sets;

void recv_file_info(int sockfd, std::set<std::string> &file_sets){
    int count;
    char bufferFST[4];
    count = recv(sockfd, bufferFST, 4, MSG_PEEK);
    if(count == -1)
        perror("Recv with error");

    google::protobuf::uint32 pkg_size = readHdr(bufferFST);
    int byteCount;
    file::Files files;
    char buffer[pkg_size + HDR_SIZE];
    if( ( byteCount = recv(sockfd, (void *)buffer, pkg_size + HDR_SIZE, MSG_WAITALL) ) == -1 ){
        perror("Error recviving data");
    }
    google::protobuf::io::ArrayInputStream ais(buffer, pkg_size + HDR_SIZE);
    google::protobuf::io::CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&pkg_size);
    google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(pkg_size);
    files.ParseFromCodedStream(&coded_input);

    for(int i=0; i<files.files_size(); ++i){
        file::File file = files.files(i);
        file_sets.insert( file.file_name() );
        std::cout << file.file_name() << '\n';
    }
}

void delete_account(int sockfd){

    printf("Into delete account function\n");

    int count;
    char bufferFST[4];
    count = recv(sockfd, bufferFST, 4, MSG_PEEK);
    if(count == -1)
        perror("Recv with error");

    login::DeleteInfo info = readDeleteInfo(sockfd, readHdr(bufferFST) );
    std::cout << info.DebugString();

    Data::Data newInfo;
    newInfo.set_id( info.id() );
    newInfo.set_password( info.passwd() );

    for(int i=0; i<loginData.logindata_size(); ++i){
        if( loginData.logindata(i).id() == newInfo.id() &&
            loginData.logindata(i).password() == newInfo.password() ){
            loginData.mutable_logindata(i)->set_id("");
            loginData.mutable_logindata(i)->set_password("");
            sendCheck(sockfd, true);
            std::fstream out(".data", std::ios::out | std::ios::trunc | std::ios::binary);
            if ( !loginData.SerializeToOstream(&out) ) {
                perror("output_file error");
            }
            out.close();
            return;
        }
    }

    sendCheck(sockfd, false);
    return;
}

void search_info(int sockfd){
    printf("Into search_info function\n");
}

void download(int sockfd){
    printf("Into download function\n");
}

void chat(int sockfd){
    printf("Into chat function\n");
}

void login_check(int sockfd){
    //recv login info
    int count;
    char bufferFST[4];
    count = recv(sockfd, bufferFST, 4, MSG_PEEK);
    if(count == -1)
        perror("Recv with error");

    login::Login login = readLogin(sockfd, readHdr(bufferFST) );
    std::cout << login.DebugString();

    //check id and password
    Data::Data newLogin;
    newLogin.set_id( login.id() );
    newLogin.set_password( login.passwd() );

    for(int i=0; i<loginData.logindata_size(); ++i){
        if( loginData.logindata(i).id() == newLogin.id() &&
            loginData.logindata(i).password() == newLogin.password() ){
            sendCheck(sockfd, true);
            return;
        }
    }

    sendCheck(sockfd, false);
    return;
}

void regist_check(int sockfd){
    //recv regist
    int count;
    char bufferFST[4];
    count = recv(sockfd, bufferFST, 4, MSG_PEEK);
    if(count == -1)
        perror("Recv with error");

    google::protobuf::uint32 size = readHdr(bufferFST);
    int byteCount;
    regist::Regist regist;
    char buffer[size + HDR_SIZE];
    if( ( byteCount = recv(sockfd, (void *)buffer, size + HDR_SIZE, MSG_WAITALL) ) == -1 ){
        perror("Error recviving data");
    }
    google::protobuf::io::ArrayInputStream ais(buffer, size + HDR_SIZE);
    google::protobuf::io::CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&size);
    google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(size);
    regist.ParseFromCodedStream(&coded_input);
    coded_input.PopLimit(msgLimit);
    std::cout << regist.DebugString();

    //check id and password
    Data::Data newRegist;
    newRegist.set_id( regist.id() );
    newRegist.set_password( regist.passwd() );

    for(int i=0; i<loginData.logindata_size(); ++i){
        if( loginData.logindata(i).id() == newRegist.id() ){
            sendCheck(sockfd, false);
            return;
        }
    }

    Data::Data* data = loginData.add_logindata();
    data -> set_id(regist.id());
    data -> set_password(regist.passwd());

    std::fstream out(".data", std::ios::out | std::ios::trunc | std::ios::binary);
    if ( !loginData.SerializeToOstream(&out) ) {
      perror("output_file error");
    }
    out.close();
    sendCheck(sockfd, true);
}

void* client_connect(void *);

int main(int argc, char** args){

    //argc error detect
    if(argc != 2){
        printf("Usage: ./server <port_num> \n");
        return 1;
    }

    //read login data
    std::fstream in(".data", std::ios::in | std::ios::binary);
    if( !loginData.ParseFromIstream(&in) ){
        printf("Failed to read data\n");
        return 0;
    }
    in.close();

    //arguments declare
	int listenFD, connectFD;
    int port_num = atoi(args[1]);
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
        printf( "Connect from %s %d\n", cli_addr, client_address->sin_port );
    	if( pthread_create( &tid, NULL, client_connect, (void *)&connectFD ) ){
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
    /*int read_size;
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

	write(sockfd, pkt, pkg_size);*/
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
            if ( request == LOGIN ) {
                login_check(sockfd);
            } else if ( request == REGIST ) {
                regist_check(sockfd);
            } else if ( request == DELETEACCOUNT ) {
                delete_account(sockfd);
            } else if ( request == SEARCHINFO ) {
                search_info(sockfd);
            } else if ( request == DOWNLOAD ) {
                download(sockfd);
            } else if ( request == CHAT ) {
                chat(sockfd);
            } else if (request == LOGOUT ) {
                break;
            } else if (request == RECVFILEINFO ) {
                recv_file_info(sockfd, file_sets);
            } else {
                printf("%sBugssssssssssss%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
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
    printf("Connection left\n");
    return 0;
}
