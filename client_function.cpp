#include <iostream>
#include "login.pb.h"
#include "regist.pb.h"
#include "action.pb.h"
#include "data_login.pb.h"
#include "check.pb.h"
#include "gdb_handle.cpp"

bool login_to_server(int sockfd){

	// send login action
	action::Action action;
	action.set_action("login");
	int pkg_size = action.ByteSize() + HDR_SIZE;
	char* pkg = new char[pkg_size];
	google::protobuf::io::ArrayOutputStream aos(pkg, pkg_size);
	google::protobuf::io::CodedOutputStream* coded_output = new google::protobuf::io::CodedOutputStream(&aos);
	coded_output -> WriteVarint32(action.ByteSize());
	action.SerializeToCodedStream(coded_output);

	write(sockfd, pkg, pkg_size);

	// send login info
	std::string account;
	std::string passwd;
	printf("Account:");
	std::cin >> account;
	printf("Password:");
	std::cin >> passwd;

	login::Login login;
	login.set_id(account);
	login.set_passwd(passwd);
	pkg_size = login.ByteSize() + HDR_SIZE;
	free(pkg);
	google::protobuf::io::ArrayOutputStream aosl(pkg, pkg_size);
	google::protobuf::io::CodedOutputStream* coded_output_l = new google::protobuf::io::CodedOutputStream(&aosl);
	coded_output_l -> WriteVarint32(login.ByteSize());
	login.SerializeToCodedStream(coded_output_l);
	std::cout << login.DebugString();

	write(sockfd, pkg, pkg_size);

	// recv login permit
	int count;
	char buffer[4];
	count = recv(sockfd, buffer, 4, MSG_PEEK);
	if(count == -1)
		printf("recv check pkg error\n");
	else{
		return readCheck(sockfd, readHdr(buffer));
	}

}

void regist_to_server(int sockfd){

	action::Action action;
	action.set_action("regist");
	int pkg_size = action.ByteSize() + HDR_SIZE;
	char* pkg = new char[pkg_size];
	google::protobuf::io::ArrayOutputStream aos(pkg, pkg_size);
	google::protobuf::io::CodedOutputStream* coded_output = new google::protobuf::io::CodedOutputStream(&aos);
	coded_output -> WriteVarint32(action.ByteSize());
	action.SerializeToCodedStream(coded_output);

	write(sockfd, pkg, pkg_size);

	std::string account;
	std::string passwd;
	std::string confirm_passwd;
	while(true){
		printf("Account:");
		std::cin >> account;
		printf("Password:");
		std::cin >> passwd;
		printf("Confirm Password:");
		std::cin >> confirm_passwd;

		if( passwd == confirm_passwd )
			break;
	}

	regist::Regist regist;
	regist.set_id(account);
	regist.set_passwd(passwd);
	pkg_size = regist.ByteSize() + HDR_SIZE;
	free(pkg);
	google::protobuf::io::ArrayOutputStream aosl(pkg, pkg_size);
	google::protobuf::io::CodedOutputStream* coded_output_l = new google::protobuf::io::CodedOutputStream(&aosl);
	coded_output_l -> WriteVarint32(regist.ByteSize());
	regist.SerializeToCodedStream(coded_output_l);
	std::cout << regist.DebugString();

	write(sockfd, pkg, pkg_size);
}

void identity(int sockfd){
	printf("[L]ogin\t[R]egist\n");
	std::string command;
	while( std::cin >> command ){
		if( command == "L" || command == "l" ){
			login_to_server(sockfd);
			break;
		}else if(command == "R" || command == "r"){
			regist_to_server(sockfd);
			break;
		}else{
			printf("Cannot identify your input\n");
		}
	}
}
