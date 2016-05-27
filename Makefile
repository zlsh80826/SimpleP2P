CXX=g++
CXXFLAGS=-std=c++11
LDFLAGS=-lpthread
all: server client
%: %.cpp