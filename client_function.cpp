#include <iostream>
#include "login.pb.h"
#include "regist.pb.h"
#include "action.pb.h"
#include "data_login.pb.h"
#include "check.pb.h"
#include "gdb_handle.cpp"
#include "define.h"

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
	delete coded_output;

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
	char* login_pkg = new char[pkg_size];
	google::protobuf::io::ArrayOutputStream aosl(login_pkg, pkg_size);
	google::protobuf::io::CodedOutputStream* coded_output_l = new google::protobuf::io::CodedOutputStream(&aosl);
	coded_output_l -> WriteVarint32(login.ByteSize());
	login.SerializeToCodedStream(coded_output_l);
	std::cout << login.DebugString();

	write(sockfd, login_pkg, pkg_size);
	delete coded_output_l;

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

bool regist_to_server(int sockfd){

	action::Action action;
	action.set_action("regist");
	int pkg_size = action.ByteSize() + HDR_SIZE;
	char* pkg = new char[pkg_size];
	google::protobuf::io::ArrayOutputStream aos(pkg, pkg_size);
	google::protobuf::io::CodedOutputStream* coded_output = new google::protobuf::io::CodedOutputStream(&aos);
	coded_output -> WriteVarint32(action.ByteSize());
	action.SerializeToCodedStream(coded_output);

	write(sockfd, pkg, pkg_size);
	delete coded_output;

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
		else{
			printf("%sYour password is invalid !%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
		}
	}

	regist::Regist regist;
	regist.set_id(account);
	regist.set_passwd(passwd);
	pkg_size = regist.ByteSize() + HDR_SIZE;
	char* reg_pkg = new char[pkg_size];
	google::protobuf::io::ArrayOutputStream aosl(reg_pkg, pkg_size);
	google::protobuf::io::CodedOutputStream* coded_output_l = new google::protobuf::io::CodedOutputStream(&aosl);
	coded_output_l -> WriteVarint32(regist.ByteSize());
	regist.SerializeToCodedStream(coded_output_l);
	std::cout << regist.DebugString();
	delete coded_output_l;
	write(sockfd, reg_pkg, pkg_size);

	// recv regist permit
	int count;
	char buffer[4];
	count = recv(sockfd, buffer, 4, MSG_PEEK);
	if(count == -1)
		printf("recv check pkg error\n");
	else{
		if( !readCheck(sockfd, readHdr(buffer)) ){
			printf("%sThis ID is used!%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
		}else{
			printf("%sRegist success%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
		}
		return false;
	}
}

bool identity(int sockfd){
	printf("---------------------------------------\n");
	printf("[L]ogin\t[R]egist\n");
	std::string command;
	while( std::cin >> command ){
		if( command == "L" || command == "l" ){
			if( login_to_server(sockfd) ){
				printf("%sLogin success%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
				return true;
			}else{
				printf("%sWrong id or password%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
				return false;
			}
		}else if(command == "R" || command == "r"){
			regist_to_server(sockfd);
			return false;
		}else{
			printf("Cannot identify your input\n");
			return false;
		}
	}
}

void logout(int sockfd){
	sendAction(sockfd, "logout");
	printf("%sGood Bye!%s\n", ANSI_COLOR_YELLOW, ANSI_COLOR_RESET);
}

bool delete_account(int sockfd){
	// check
	printf("%s[Warning]%s Are you sure delete account ?(N/y)\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
	std::string NY;
	std::cin >> NY;
	if( NY != "y" && NY != "yes" )
		return false;

	// get user info
	sendAction(sockfd, "deleteaccount");
	std::string account;
	std::string password;
	printf("Confirm ID:");
	std::cin >> account;
	printf("Confirm Password:");
	std::cin >> password;

	// send info
	login::DeleteInfo info;
	info.set_id(account);
	info.set_passwd(password);
	int pkg_size = info.ByteSize() + HDR_SIZE;
	char* pkg = new char[pkg_size];
	google::protobuf::io::ArrayOutputStream aos(pkg, pkg_size);
	google::protobuf::io::CodedOutputStream* coded_output = new google::protobuf::io::CodedOutputStream(&aos);
	coded_output -> WriteVarint32(info.ByteSize());
	info.SerializeToCodedStream(coded_output);

	write(sockfd, pkg, pkg_size);
	delete coded_output;

	// check server react
	int count;
	char buffer[4];
	count = recv(sockfd, buffer, 4, MSG_PEEK);
	if(count == -1)
		printf("recv check pkg error\n");
	else{
		if( !readCheck(sockfd, readHdr(buffer)) ){
			printf("%sPermission denied%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
		}else{
			printf("%sDelete success%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
			logout(sockfd);
			return true;
		}
		return false;
	}
	return false;
}

void search_info(int sockfd){
	printf("Into search_info function\n");
	sendAction(sockfd, "searchinfo");
}

void download(int sockfd){
	printf("Into download function\n");
	sendAction(sockfd, "download");
}

void chat(int sockfd){
	printf("Into chat function\n");
	sendAction(sockfd, "chat");
}

