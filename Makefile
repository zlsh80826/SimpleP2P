CXX=g++
CXXFLAGS=-std=c++11
LDFLAGS=-lpthread -pthread -lprotobuf

.PHONY: all
all: server client

server: server.o login.pb.o action.pb.o download_info.pb.o regist.pb.o data_login.pb.o check.pb.o file.pb.o online.pb.o port.pb.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) server.o download_info.pb.o regist.pb.o data_login.pb.o login.pb.o action.pb.o port.pb.o online.pb.o check.pb.o file.pb.o -o server
client: client.o login.pb.o action.pb.o download_info.pb.o regist.pb.o data_login.pb.o check.pb.o file.pb.o port.pb.o online.pb.o client_function.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) client.o download_info.pb.o regist.pb.o data_login.pb.o login.pb.o action.pb.o port.pb.o online.pb.o check.pb.o file.pb.o -o client
server.o: server.cpp

client.o: client.cpp

login.pb.o: login.pb.cpp login.pb.h

regist.pb.o: regist.pb.cpp regist.pb.h

action.pb.o: action.pb.cpp action.pb.h

data_login.pb.o: data_login.pb.cpp data_login.pb.h

check.pb.o: check.pb.cpp check.pb.h

file.pb.o: file.pb.cpp file.pb.h

online.pb.o: online.pb.cpp online.pb.h

port.pb.o: port.pb.cpp port.pb.h

download_info.pb.o: download_info.pb.cpp download_info.pb.h

.PHONY: clean
clean:
	rm -rf ./*.o client server
