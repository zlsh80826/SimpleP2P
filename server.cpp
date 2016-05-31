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
#include <time.h>
#include <map>
#include <set>
#define BACKLOG 30
Data::LoginData loginData;
std::map< std::string, std::set<std::string> > file_sets;

void send_port(int sockfd, int port_num, std::string ip){
    port::Port port;
    port.set_port_num(port_num);
    port.set_ip(ip);

    int pkg_size = port.ByteSize() + HDR_SIZE;
    char* pkg = new char[pkg_size];
    google::protobuf::io::ArrayOutputStream aos(pkg, pkg_size);
    google::protobuf::io::CodedOutputStream* coded_output = new google::protobuf::io::CodedOutputStream(&aos);
    coded_output -> WriteVarint32(port.ByteSize());
    port.SerializeToCodedStream(coded_output);

    write(sockfd, pkg, pkg_size);
    delete coded_output;
}

void send_online_info(int sockfd){
    online::OnlineSheet sheet;
    for(int i=0; i<loginData.logindata_size(); ++i){
        if( loginData.logindata(i).online() == true){
            if( loginData.logindata(i).id() != "" ){
                online::OnlinePerson* person;
                person = sheet.add_sheets();
                person->set_name(loginData.logindata(i).id());
            }
        }
    }

    int pkg_size = sheet.ByteSize() + HDR_SIZE;
    char* pkg = new char[pkg_size];
    google::protobuf::io::ArrayOutputStream aos(pkg, pkg_size);
    google::protobuf::io::CodedOutputStream* coded_output = new google::protobuf::io::CodedOutputStream(&aos);
    coded_output -> WriteVarint32(sheet.ByteSize());
    sheet.SerializeToCodedStream(coded_output);

    write(sockfd, pkg, pkg_size);
    delete coded_output;
}

void update(){
    printf("-----------------------------------\n");
    printf("%s[online]\n", ANSI_COLOR_GREEN);
    for(int i=0; i<loginData.logindata_size(); ++i){
        if( loginData.logindata(i).online() == true){
            if( loginData.logindata(i).id() != "" )
                std::cout << loginData.logindata(i).id() << '\n';
        }
    }
    printf("%s[offline]\n", ANSI_COLOR_RED);
    for(int i=0; i<loginData.logindata_size(); ++i){
        if( loginData.logindata(i).online() == false){
            if( loginData.logindata(i).id() != "" )
                std::cout << loginData.logindata(i).id() << '\n';
        }
    }
    printf("%s-----------------------------------\n", ANSI_COLOR_RESET);

    std::fstream out(".data", std::ios::out | std::ios::trunc | std::ios::binary);
    if ( !loginData.SerializeToOstream(&out) ) {
        perror("output_file error");
    }
    out.close();
}

void print_file(std::set<std::string> &file){
    if(file.empty())
        return;
    for(auto it=file.begin(); it!=file.end(); ++it){
        std::cout << " " << *it;
    }
    std::cout << '\n';
}

void logout_update(int sockfd, std::map<std::string, std::set<std::string> > &file_sets, std::string name){
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

    printf("%s\nFile update:\n ", ANSI_COLOR_GREEN);
    for(int i=0; i<files.files_size(); ++i){
        file::File file = files.files(i);
        if( file_sets.find( file.file_name() ) == file_sets.end() ){
            std::cout << "Bugssssssssssss" << std::endl;
        }else{
            file_sets[file.file_name()].erase(name);
            if( !file_sets[file.file_name()].empty() ){
                std::cout << file.file_name() << ":" ;
                print_file(file_sets[file.file_name()]);
            }
        }
    }
    printf("%s\n", ANSI_COLOR_RESET);
    update();
}

void logout(int sockfd, std::map<std::string, std::set<std::string> > &file_sets){
    //recv logout info
    int count;
    char bufferFST[4];
    count = recv(sockfd, bufferFST, 4, MSG_PEEK);
    if(count == -1)
        perror("Recv with error");

    login::Login login = readLogin(sockfd, readHdr(bufferFST) );
    //std::cout << login.DebugString();

    //check id and password
    Data::Data newLogin;
    newLogin.set_id( login.id() );
    newLogin.set_password( login.passwd() );

    for(int i=0; i<loginData.logindata_size(); ++i){
        if( loginData.logindata(i).id() == newLogin.id() &&
            loginData.logindata(i).password() == newLogin.password() ){
            sendCheck(sockfd, true);
            tm* ptr_now;
            time_t loc_now = 0;
            time(&loc_now);
            std::string id = loginData.logindata(i).id();
            loginData.mutable_logindata(i)->set_online(false);
            ptr_now = localtime(&loc_now);
            printf("%s[%d:%d:%d] : [%s] logout %s\n", ANSI_COLOR_RED
            , ptr_now->tm_hour, ptr_now->tm_min, ptr_now->tm_sec, id.c_str(), ANSI_COLOR_RESET);
            logout_update(sockfd, file_sets, login.id());
            return;
        }
    }
    return;
}

void recv_file_info(int sockfd, std::map<std::string, std::set<std::string> > &file_sets, login::Login user){
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

    printf("%sFile update: ", ANSI_COLOR_GREEN);
    for(int i=0; i<files.files_size(); ++i){
        file::File file = files.files(i);
        if( file_sets.find( file.file_name() ) == file_sets.end() ){
            file_sets[file.file_name()].insert(user.id());
            std::cout << file.file_name() << ":";
            print_file(file_sets[file.file_name()]);
        }
        else{
            file_sets[file.file_name()].insert(user.id());
            std::cout << file.file_name() << ":";
            print_file(file_sets[file.file_name()]);
        }
    }
    printf("%s\n", ANSI_COLOR_RESET);
    update();
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
            loginData.mutable_logindata(i)->set_online(false);
            sendCheck(sockfd, true);
            update();
        }
    }

    sendCheck(sockfd, false);
    return;
}

void search_info(int sockfd){
    file::Files files;
    for(auto items=file_sets.begin(); items!=file_sets.end(); ++items){
        file::File* file = files.add_files();
        file->set_file_name(items -> first );
        //std::cout << file->DebugString();
    }

    int pkg_size = files.ByteSize() + HDR_SIZE;
    char* pkg = new char[pkg_size];
    google::protobuf::io::ArrayOutputStream aos(pkg, pkg_size);
    google::protobuf::io::CodedOutputStream* coded_output = new google::protobuf::io::CodedOutputStream(&aos);
    coded_output -> WriteVarint32(files.ByteSize());
    files.SerializeToCodedStream(coded_output);

    write(sockfd, pkg, pkg_size);
    delete coded_output;
}

void send_download_info(int sockfd, std::set<std::string>& peer_set){
    download::DownloadInfo peer_info;
    for(auto it=peer_set.begin(); it!=peer_set.end(); ++it){
        for(int i=0; i<loginData.logindata_size(); ++i){
            if( loginData.logindata(i).id() == *it &&
                loginData.logindata(i).online() == true ) {
                download::Peer* peer = peer_info.add_peer_info();
                peer->set_ip(loginData.logindata(i).ip());
                peer->set_port(loginData.logindata(i).port());
            }
        }
    }
    peer_info.set_file_byte_size(peer_set.size());

    int pkg_size = peer_info.ByteSize() + HDR_SIZE;
    char* pkg = new char[pkg_size];
    google::protobuf::io::ArrayOutputStream aos(pkg, pkg_size);
    google::protobuf::io::CodedOutputStream* coded_output = new google::protobuf::io::CodedOutputStream(&aos);
    coded_output -> WriteVarint32(peer_info.ByteSize());
    peer_info.SerializeToCodedStream(coded_output);

    write(sockfd, pkg, pkg_size);
    delete coded_output;
}

void download_p2p(int sockfd){

    int count;
    char bufferFST[4];
    count = recv(sockfd, bufferFST, 4, MSG_PEEK);
    if(count == -1)
        perror("Recv with error");

    google::protobuf::uint32 pkg_size = readHdr(bufferFST);
    int byteCount;
    file::File request_file;
    char buffer[pkg_size + HDR_SIZE];
    if( ( byteCount = recv(sockfd, (void *)buffer, pkg_size + HDR_SIZE, MSG_WAITALL) ) == -1 ){
        perror("Error recviving data");
    }
    google::protobuf::io::ArrayInputStream ais(buffer, pkg_size + HDR_SIZE);
    google::protobuf::io::CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&pkg_size);
    google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(pkg_size);
    request_file.ParseFromCodedStream(&coded_input);

    for(auto it=file_sets.begin(); it!=file_sets.end(); ++it){
        if( it-> first == request_file.file_name() && !it->second.empty() ){
            sendCheck(sockfd, true);
            send_download_info(sockfd, it->second);
            return;
        }
    }
    sendCheck(sockfd, false);
    return;
}

void chat(int sockfd){

    // recv name
    int count;
    char bufferFST[4];
    count = recv(sockfd, bufferFST, 4, MSG_PEEK);
    if(count == -1)
        perror("Recv with error");

    google::protobuf::uint32 pkg_size = readHdr(bufferFST);
    int byteCount;
    online::OnlinePerson person;
    char buffer[pkg_size + HDR_SIZE];
    if( ( byteCount = recv(sockfd, (void *)buffer, pkg_size + HDR_SIZE, MSG_WAITALL) ) == -1 ){
        perror("Error recviving data");
    }
    google::protobuf::io::ArrayInputStream ais(buffer, pkg_size + HDR_SIZE);
    google::protobuf::io::CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&pkg_size);
    google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(pkg_size);
    person.ParseFromCodedStream(&coded_input);

    // check whether online
    for(int i=0; i<loginData.logindata_size(); ++i){
        if( loginData.logindata(i).online() == true ){
            if( loginData.logindata(i).id() != "" &&
                loginData.logindata(i).id() == person.name() ){
                sendCheck(sockfd, true);
                send_port(sockfd, loginData.logindata(i).port(), loginData.logindata(i).ip());
                return;
            }
        }
    }
    sendCheck(sockfd, false);
    printf("!ok\n");

}

login::Login login_check(int sockfd, std::string addr, int port){
    //recv login info
    int count;
    char bufferFST[4];
    count = recv(sockfd, bufferFST, 4, MSG_PEEK);
    if(count == -1)
        perror("Recv with error");

    login::Login login = readLogin(sockfd, readHdr(bufferFST) );
    //std::cout << login.DebugString();

    //check id and password
    Data::Data newLogin;
    newLogin.set_id( login.id() );
    newLogin.set_password( login.passwd() );

    for(int i=0; i<loginData.logindata_size(); ++i){
        if( loginData.logindata(i).id() == newLogin.id() &&
            loginData.logindata(i).password() == newLogin.password() ){
            sendCheck(sockfd, true);
            tm* ptr_now;
            time_t loc_now = 0;
            time(&loc_now);
            std::string id = loginData.logindata(i).id();
            loginData.mutable_logindata(i)->set_online(true);
            loginData.mutable_logindata(i)->set_ip(addr);
            loginData.mutable_logindata(i)->set_port(login.port());
            ptr_now = localtime(&loc_now);
            printf("%s[%d:%d:%d] : [%s] login %s\n", ANSI_COLOR_GREEN
            , ptr_now->tm_hour, ptr_now->tm_min, ptr_now->tm_sec, id.c_str(), ANSI_COLOR_RESET);
            //std::cout << loginData.logindata(i).DebugString();
            return login;
        }
    }

    sendCheck(sockfd, false);
    return login;
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
    //std::cout << regist.DebugString();

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

    update();
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
        std::string addr(cli_addr);
        thread_info* info = new thread_info(connectFD, addr, client_address->sin_port);
        //printf( "Connect from %s %d\n", cli_addr, client_address->sin_port );
    	if( pthread_create( &tid, NULL, client_connect, (void *)info ) ){
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

void* client_connect(void* info){
    thread_info* new_info = (thread_info* )info;
    int sockfd = new_info -> sockfd;
    std::string addr = new_info -> address;
    int port = new_info -> port;

    std::cout << sockfd << " " << addr << " " << port << '\n';
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
    update();
    login::Login login;
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
                login = login_check(sockfd, addr, port);
            } else if ( request == REGIST ) {
                regist_check(sockfd);
            } else if ( request == DELETEACCOUNT ) {
                delete_account(sockfd);
            } else if ( request == SEARCHINFO ) {
                search_info(sockfd);
            } else if ( request == DOWNLOAD ) {
                download_p2p(sockfd);
            } else if ( request == CHAT ) {
                chat(sockfd);
            } else if (request == LOGOUT ) {
                logout(sockfd, file_sets);
                break;
            } else if (request == RECVFILEINFO ) {
                recv_file_info(sockfd, file_sets, login);
            } else if (request == ONLINEINFO){
                send_online_info(sockfd);
            } else if (request == PORTREQUEST) {
                //send_port(sockfd);
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
    //printf("Connection left\n");
    return 0;
}
