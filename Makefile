CXX=g++
CXXFLAGS=-std=c++11
LDFLAGS=-lpthread -lprotobuf

.PHONY: all
all: server client

server: server.o login.pb.o action.pb.o regist.pb.o data_login.pb.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) server.o regist.pb.o data_login.pb.o login.pb.o action.pb.o -o server
client: client.o login.pb.o action.pb.o regist.pb.o data_login.pb.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) client.o regist.pb.o data_login.pb.o login.pb.o action.pb.o -o client
server.o: server.cpp

client.o: client.cpp

login.pb.o: login.pb.cpp login.pb.h

regist.pb.o: regist.pb.cpp regist.pb.h

action.pb.o: action.pb.cpp action.pb.h

data_login.pb.o: data_login.pb.cpp data_login.pb.h

.PHONY: clean
clean:
	rm -rf ./*.o client server
