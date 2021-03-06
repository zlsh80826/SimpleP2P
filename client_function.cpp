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
#define MAXLINE 4096
#define MAX_ 1024

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

port::Port get_port(int sockfd){

    int count;
    char bufferFST[4];
    count = recv(sockfd, bufferFST, 4, MSG_PEEK);
    if(count == -1)
        perror("Recv with error");

    google::protobuf::uint32 pkg_size = readHdr(bufferFST);
    int byteCount;
    port::Port port;
    char buffer[pkg_size + HDR_SIZE];
    if( ( byteCount = recv(sockfd, (void *)buffer, pkg_size + HDR_SIZE, MSG_WAITALL) ) == -1 ){
        perror("Error recviving data");
    }
    google::protobuf::io::ArrayInputStream ais(buffer, pkg_size + HDR_SIZE);
    google::protobuf::io::CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&pkg_size);
    google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(pkg_size);
    port.ParseFromCodedStream(&coded_input);
    return port;
}

int connect_to_peer(int sock){
	std::cout << std::endl;
	port::Port peer_info = get_port(sock);
	struct sockaddr_in server_address;
	int sockfd;
	// create connect descriptor
	if( (sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0 )
		perror("socket create error");
	//setting server_address
	bzero( &server_address, sizeof(server_address) );
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(peer_info.port_num());
	if( inet_pton(AF_INET, peer_info.ip().c_str(), &server_address.sin_addr) <= 0 ){
		printf("Can't identify IP address %s \n", peer_info.ip().c_str());
		return 1;
	}
	if( connect(sockfd, (sockaddr* )(&server_address), sizeof(server_address)) < 0 ){
		perror("connect error");
		return 1;
	}

	sendAction(sockfd, "messagetopeer");

	char sendline[MAXLINE];

	memset(sendline, 0, sizeof(sendline));
	std::string str;
	printf("Message:");
	while( std::cin >> str ){
		if(std::cin.eof() || str == "q"){
			write(sockfd, "q", 1);
			break;
		}
		printf("Message:");
		write(sockfd, str.c_str(), str.length());
	}
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
	int pkg_sizeF = user.ByteSize() + HDR_SIZE;
	char* login_pkg = new char[pkg_sizeF];
	google::protobuf::io::ArrayOutputStream aosl(login_pkg, pkg_sizeF);
	google::protobuf::io::CodedOutputStream* coded_output_l = new google::protobuf::io::CodedOutputStream(&aosl);
	coded_output_l -> WriteVarint32(user.ByteSize());
	user.SerializeToCodedStream(coded_output_l);
	//std::cout << user.DebugString();

	write(sockfd, login_pkg, pkg_sizeF);
	delete coded_output_l;

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
	if( user.passwd() != password ){
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

int start_download(int index, download::DownloadInfo info, std::string file_name, int peer_num){
	struct sockaddr_in server_address;
	int sockfd;
	int index_ = index;
	int total = peer_num;
	// create connect descriptor
	if( (sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0 )
		perror("socket create error");
	//setting server_address
	bzero( &server_address, sizeof(server_address) );
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons( info.peer_info(index).port() );
	if( inet_pton(AF_INET, info.peer_info(index).ip().c_str(), &server_address.sin_addr) <= 0 ){
		printf("Can't identify IP address %s \n", info.peer_info(index).ip().c_str());
		return 1;
	}
	if( connect(sockfd, (sockaddr* )(&server_address), sizeof(server_address)) < 0 ){
		perror("connect error");
		return 1;
	}


	sendAction(sockfd, "askfile");
	// printf("client ask file with %d\n", index);

	// steal file
	FILE* file_ptr;
	file_ptr = fopen(file_name.c_str(), "rb+");
	char message[48];
	strcpy(message, file_name.c_str());
	// send file name
	int file_name_size = file_name.size();
	send(sockfd, &file_name_size, sizeof(file_name_size), 0);
	send(sockfd, message, file_name.size(), 0);
	send(sockfd, &index_, sizeof(index_), 0);
	send(sockfd, &total, sizeof(total), 0);

	// get file size
	long long file_size;
	recv(sockfd, &file_size, sizeof(file_size), 0);
	printf("%lld\n", file_size);

	fseek(file_ptr, (file_size/total) * index, SEEK_SET);
	printf("%d: Seek_to:%d\n", index, (file_size/total) * index);

	if( index == total-1 ){
		file_size = file_size - (file_size/total)*index;
	}else{
		file_size = (file_size/total);
	}
	printf("%d: Deal_size:%d\n", index, file_size);


	printf("Start:\n");
	while(true){

		int tmp = ftell(file_ptr);

		int pack_size;
		recv(sockfd, &pack_size, sizeof(pack_size), MSG_WAITALL);
		if(pack_size == -1)
			break;
		char buf[pack_size];
		memset(buf, 0, sizeof(buf));
		int c = recv(sockfd, buf, pack_size, MSG_WAITALL);

		fwrite(buf, 1, sizeof(buf), file_ptr);

		printf("%d: write %d~%d\n", index, tmp, ftell(file_ptr));
		file_size -= pack_size;
	}
	printf("end\n");
	fclose(file_ptr);
}

void download_divide(int sockfd, download::DownloadInfo info, std::string file_name){
	int peer_num = info.file_byte_size();
	FILE* file_ptr;
	file_ptr = fopen(file_name.c_str(), "wb");
	fclose(file_ptr);

	for(int i=0; i<peer_num; ++i){
		std::thread downloadThread(start_download, i, info, file_name, peer_num);
		printf("before detach");
		downloadThread.detach();
		printf("after detach");
	}
}

void get_download_info(int sockfd, std::string file_name){
    int count;
    char bufferFST[4];
    count = recv(sockfd, bufferFST, 4, MSG_PEEK);
    if(count == -1)
        perror("Recv with error");

    google::protobuf::uint32 pkg_size = readHdr(bufferFST);
    int byteCount;
    download::DownloadInfo info;
    char buffer[pkg_size + HDR_SIZE];
    if( ( byteCount = recv(sockfd, (void *)buffer, pkg_size + HDR_SIZE, MSG_WAITALL) ) == -1 ){
        perror("Error recviving data");
    }
    google::protobuf::io::ArrayInputStream ais(buffer, pkg_size + HDR_SIZE);
    google::protobuf::io::CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&pkg_size);
    google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(pkg_size);
    info.ParseFromCodedStream(&coded_input);

    std::cout << info.DebugString();
    download_divide(sockfd, info, file_name);
}

void download_p2p(int sockfd){
	printf("File name: ");
	std::string file_name;
	std::cin >> file_name;
	std::string dir(".");
	std::vector<std::string> files_vec;
    getdir(dir, files_vec);
    for(auto it=files_vec.begin(); it!=files_vec.end(); it++){
    	if( *it == file_name ){
			printf("%sYou already have this file%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
			return;
    	}
    }

    // send download action
    sendAction(sockfd, "download");
	file::File request_file;
	request_file.set_file_name(file_name);

	int pkg_size = request_file.ByteSize() + HDR_SIZE;
	char* pkg = new char[pkg_size];
	google::protobuf::io::ArrayOutputStream aos(pkg, pkg_size);
	google::protobuf::io::CodedOutputStream* coded_output = new google::protobuf::io::CodedOutputStream(&aos);
	coded_output -> WriteVarint32(request_file.ByteSize());
	request_file.SerializeToCodedStream(coded_output);

	write(sockfd, pkg, pkg_size);
	delete coded_output;

	int count;
	char buffer[4];
	count = recv(sockfd, buffer, 4, MSG_PEEK);
	if(count == -1){
		printf("recv check pkg error\n");
	}else{
		if( readCheck(sockfd, readHdr(buffer)) ){
			get_download_info(sockfd, file_name);
			printf("ok\n");
		}else{
			printf("%sNo such file%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
		}
	}

}

void chat(int sockfd, login::Login user){
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
			printf("%sHe(she) is offline%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
		}else{
			//printf("%sRecv ok%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
			std::thread connectThread(connect_to_peer, sockfd);
			connectThread.join();
			//printf("?\n");
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
