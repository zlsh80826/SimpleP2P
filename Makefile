CXX=g++
CXXFLAGS=-std=c++11
LDFLAGS=-lpthread

all: server client

server: server.o info.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) server.o info.o -o server
client: client.o info.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) client.o info.o -o client
server.o: server.cpp 

client.o: client.cpp

info.o: info.cpp info.h

clean:
	rm -rf ./*.o