#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <iostream>
#define HDR_SIZE 4
enum ACTION{LOGIN, REGIST, UNDEFINE};

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
