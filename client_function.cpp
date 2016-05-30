#include <iostream>
#include <vector>
#include <dirent.h>
#include "login.pb.h"
#include "regist.pb.h"
#include "action.pb.h"
#include "data_login.pb.h"
#include "check.pb.h"
#include "gdb_handle.cpp"
#include "file.pb.h"
#include "port.pb.h"
#include "define.h"

int get_port(int sockfd){
	sendAction(sockfd, "portrequest");
}

void connect_to_peer(int sockfd){
	int port = get_port(sockfd);
}

bool login_to_server(int sockfd, login::Login* user, int* port){

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
	login.set_port(*port);
	pkg_size = login.ByteSize() + HDR_SIZE;
	char* login_pkg = new char[pkg_size];
	google::protobuf::io::ArrayOutputStream aosl(login_pkg, pkg_size);
	google::protobuf::io::CodedOutputStream* coded_output_l = new google::protobuf::io::CodedOutputStream(&aosl);
	coded_output_l -> WriteVarint32(login.ByteSize());
	login.SerializeToCodedStream(coded_output_l);
	//std::cout << login.DebugString();

	write(sockfd, login_pkg, pkg_size);
	delete coded_output_l;

	// recv login permit
	int count;
	char buffer[4];
	count = recv(sockfd, buffer, 4, MSG_PEEK);
	if(count == -1)
		printf("recv check pkg error\n");
	else{
		if(readCheck(sockfd, readHdr(buffer))){
			user->set_id(login.id());
			user->set_passwd(login.passwd());
			return true;
		}
		return false;
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
	//std::cout << regist.DebugString();
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

bool identity(int sockfd, login::Login* user, int* port){
	printf("---------------------------------------\n");
	printf("[L]ogin\t[R]egist\n");
	std::string command;
	while( std::cin >> command ){
		if( command == "L" || command == "l" ){
			if( login_to_server(sockfd, user, port) ){
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

void logout(int sockfd, login::Login user){
	sendAction(sockfd, "logout");
	int pkg_size = user.ByteSize() + HDR_SIZE;
	char* login_pkg = new char[pkg_size];
	google::protobuf::io::ArrayOutputStream aosl(login_pkg, pkg_size);
	google::protobuf::io::CodedOutputStream* coded_output_l = new google::protobuf::io::CodedOutputStream(&aosl);
	coded_output_l -> WriteVarint32(user.ByteSize());
	user.SerializeToCodedStream(coded_output_l);
	//std::cout << user.DebugString();

	write(sockfd, login_pkg, pkg_size);
	delete coded_output_l;

	printf("%sGood Bye!%s\n", ANSI_COLOR_YELLOW, ANSI_COLOR_RESET);
}

bool delete_account(int sockfd, login::Login user){
	// check
	printf("%s[Warning]%s Are you sure delete account ?(N/y)\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
	std::string NY;
	std::cin >> NY;
	if( NY != "y" && NY != "yes" )
		return false;

	// get user info
	std::string account;
	std::string password;
	printf("Confirm ID:");
	std::cin >> account;
	if( user.id() != account ){
		printf("%sYou can only suicide!%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
		return false;
	}
	printf("Confirm Password:");
	std::cin >> password;
	if( user.id() != password ){
		printf("%sWrong password!%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
		return false;
	}

	sendAction(sockfd, "deleteaccount");
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
			logout(sockfd, user);
			return true;
		}
		return false;
	}
	return false;
}

int getdir(std::string dir, std::vector<std::string>& files){
	DIR *dp;
	dirent* dirp;
	if((dp = opendir(dir.c_str())) == NULL)
		return false;
	while( (dirp = readdir(dp)) != NULL ){
		if( strcmp(dirp->d_name, ".")  && strcmp(dirp->d_name, "..") )
			files.push_back(std::string(dirp->d_name));
	}
	closedir(dp);
	return true;
}

void search_info(int sockfd){
	sendAction(sockfd, "searchinfo");

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

    printf("%sFile: ", ANSI_COLOR_GREEN);
    for(int i=0; i<files.files_size(); ++i){
        std::cout << files.files(i).file_name();
        if( i != files.files_size()-1 )
            std::cout << ", ";
    }
    printf("%s\n", ANSI_COLOR_RESET);
}

void download(int sockfd){
	printf("Into download function\n");
	sendAction(sockfd, "download");
}

void chat(int sockfd, login::Login user){
	printf("Into chat function\n");

	printf("With: ");
	std::string person_name;
	std::cin >> person_name;

	if( person_name == user.id() ){
		printf("%sYou can't chat with yourself%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
		return;
	}

	sendAction(sockfd, "chat");

	online::OnlinePerson person;
	person.set_name(person_name);

	int pkg_size = person.ByteSize() + HDR_SIZE;
	char* pkg = new char[pkg_size];
	google::protobuf::io::ArrayOutputStream aos(pkg, pkg_size);
	google::protobuf::io::CodedOutputStream* coded_output = new google::protobuf::io::CodedOutputStream(&aos);
	coded_output -> WriteVarint32(person.ByteSize());
	person.SerializeToCodedStream(coded_output);

	write(sockfd, pkg, pkg_size);
	delete coded_output;

	int count;
	char buffer[4];
	count = recv(sockfd, buffer, 4, MSG_PEEK);
	if(count == -1){
		printf("recv check pkg error\n");
	}else{
		if( !readCheck(sockfd, readHdr(buffer)) ){
			printf("%sRecv !ok%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
		}else{
			printf("%sRecv ok%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
			connect_to_peer(sockfd);
		}
		return;
	}

}


void sendFileInfo(int sockfd){
	sendAction(sockfd, "sendfileinfo");
	std::string dir(".");
	std::vector<std::string> files_vec;
    getdir(dir, files_vec);

    file::Files files;
    for(int i=0; i<files_vec.size(); ++i){
    	file::File* file = files.add_files();
    	file->set_file_name(files_vec[i]);
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

bool get_onlien_info(int sockfd){
	sendAction(sockfd, "onlineinfo");

    int count;
    char bufferFST[4];
    count = recv(sockfd, bufferFST, 4, MSG_PEEK);
    if(count == -1)
        perror("Recv with error");

    google::protobuf::uint32 pkg_size = readHdr(bufferFST);
    int byteCount;
    online::OnlineSheet sheet;
    char buffer[pkg_size + HDR_SIZE];
    if( ( byteCount = recv(sockfd, (void *)buffer, pkg_size + HDR_SIZE, MSG_WAITALL) ) == -1 ){
        perror("Error recviving data");
    }
    google::protobuf::io::ArrayInputStream ais(buffer, pkg_size + HDR_SIZE);
    google::protobuf::io::CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&pkg_size);
    google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(pkg_size);
    sheet.ParseFromCodedStream(&coded_input);

    printf("%sOnline: ", ANSI_COLOR_GREEN);
    for(int i=0; i<sheet.sheets_size(); ++i){
        std::cout << "\n" << sheet.sheets(i).name();
    }
    printf("%s\n", ANSI_COLOR_RESET);
}
