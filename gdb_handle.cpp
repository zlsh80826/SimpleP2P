#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/repeated_field.h>
#include "login.pb.h"
#include "action.pb.h"
#include "regist.pb.h"
#include "data_login.pb.h"
#include "check.pb.h"
#include "file.pb.h"
#include "online.pb.h"
#include "port.pb.h"
#include <iostream>
#define HDR_SIZE 4
enum ACTION{LOGIN, REGIST, DELETEACCOUNT, SEARCHINFO, DOWNLOAD, CHAT, LOGOUT, RECVFILEINFO, ONLINEINFO, PORTREQUEST, UNDEFINE};

struct thread_info{
    int sockfd;
    std::string address;
    int port;

    thread_info(int sockfd, std::string address, int port){
        this->sockfd = sockfd;
        this->address = address;
        this->port = port;
    }
};

google::protobuf::uint32 readHdr(char *buf){
	google::protobuf::uint32 size;
	google::protobuf::io::ArrayInputStream ais(buf,4);
	google::protobuf::io::CodedInputStream coded_input(&ais);
	coded_input.ReadVarint32(&size); //Decode the HDR and get the size
	//cout<<"size of payload is "<<size<<endl;
	return size;
}

void readBody(int csock, google::protobuf::uint32 siz){
	int byteCount;
	login::Login login;
	char buffer[siz+4];
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

ACTION readAction(int csock, google::protobuf::uint32 size){
    //recv action
    int byteCount;
    action::Action action;
    char buffer[size + HDR_SIZE];
    if( ( byteCount = recv(csock, (void *)buffer, size + HDR_SIZE, MSG_WAITALL) )== -1 ){
        perror("Error recviving data");
    }
    google::protobuf::io::ArrayInputStream ais(buffer, size + HDR_SIZE);
    google::protobuf::io::CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&size);
    google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(size);
    action.ParseFromCodedStream(&coded_input);

    //parse action
    if( action.action() == "login" )
        return LOGIN;
    if( action.action() == "regist" )
        return REGIST;
    if( action.action() == "deleteaccount" )
        return DELETEACCOUNT;
    if( action.action() == "searchinfo" )
        return SEARCHINFO;
    if( action.action() == "download" )
        return DOWNLOAD;
    if( action.action() == "chat" )
        return CHAT;
    if( action.action() == "logout" )
        return LOGOUT;
    if( action.action() == "sendfileinfo" )
        return RECVFILEINFO;
    if( action.action() == "onlineinfo" )
        return ONLINEINFO;
    if( action.action() == "portrequest" )
        return PORTREQUEST;
    return UNDEFINE;
 }

bool readCheck(int csock, google::protobuf::uint32 size){
    //recv check
    int byteCount;
    check::Check check;
    char buffer[size + HDR_SIZE];
    if( ( byteCount = recv(csock, (void *)buffer, size + HDR_SIZE, MSG_WAITALL) )== -1 ){
        perror("Error recviving data");
    }
    google::protobuf::io::ArrayInputStream ais(buffer, size + HDR_SIZE);
    google::protobuf::io::CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&size);
    google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(size);
    check.ParseFromCodedStream(&coded_input);

    //parse check
    if( check.check() == true )
        return true;
    return false;
}

void sendAction(int sockfd, std::string act){
    action::Action action;
    action.set_action(act);
    int pkg_size = action.ByteSize() + HDR_SIZE;
    char* pkg = new char[pkg_size];
    google::protobuf::io::ArrayOutputStream aos(pkg, pkg_size);
    google::protobuf::io::CodedOutputStream* coded_output = new google::protobuf::io::CodedOutputStream(&aos);
    coded_output -> WriteVarint32(action.ByteSize());
    action.SerializeToCodedStream(coded_output);

    write(sockfd, pkg, pkg_size);
    delete coded_output;
}

login::Login readLogin(int csock, google::protobuf::uint32 size){
    //recv login
    int byteCount;
    login::Login login;
    char buffer[size + HDR_SIZE];
    if( ( byteCount = recv(csock, (void *)buffer, size + HDR_SIZE, MSG_WAITALL) )== -1 ){
        perror("Error recviving data");
    }
    google::protobuf::io::ArrayInputStream ais(buffer, size + HDR_SIZE);
    google::protobuf::io::CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&size);
    google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(size);
    login.ParseFromCodedStream(&coded_input);

    return login;
}

void sendCheck(int sockfd, bool flags){
    check::Check check;
    check.set_check(flags);
    int pkg_size = check.ByteSize() + 4;
    char* pkt = new char[pkg_size];
    google::protobuf::io::ArrayOutputStream aos(pkt, pkg_size);
    google::protobuf::io::CodedOutputStream* coded_output = new google::protobuf::io::CodedOutputStream(&aos);
    coded_output -> WriteVarint32(check.ByteSize());
    check.SerializeToCodedStream(coded_output);

    write(sockfd, pkt, pkg_size);
}

login::DeleteInfo readDeleteInfo(int csock, google::protobuf::uint32 size){
    //recv login
    int byteCount;
    login::DeleteInfo info;
    char buffer[size + HDR_SIZE];
    if( ( byteCount = recv(csock, (void *)buffer, size + HDR_SIZE, MSG_WAITALL) )== -1 ){
        perror("Error recviving data");
    }
    google::protobuf::io::ArrayInputStream ais(buffer, size + HDR_SIZE);
    google::protobuf::io::CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&size);
    google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(size);
    info.ParseFromCodedStream(&coded_input);

    return info;
}
