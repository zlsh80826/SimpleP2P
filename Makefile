CXX=g++
CXXFLAGS=-std=c++11
LDFLAGS=-lpthread -lprotobuf

.PHONY: all
all: server client

server: server.o info.o login.pb.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) server.o info.o login.pb.o -o server
client: client.o info.o login.pb.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) client.o info.o login.pb.o -o client
server.o: server.cpp

client.o: client.cpp

info.o: info.cpp info.h

login.pb.o: login.pb.cpp login.pb.h

#regist.pb.o: regist.pb.cpp regist.pb.h

.PHONY: clean
clean:
	rm -rf ./*.o client server
