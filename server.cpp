#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
using namespace std;

void* client_connect(void *);

int main(){
	//testbranch command
	int listenFD, connectFD;
	pthread_t tid;
	socklen_t addrlen, len;
	sockaddr_in* client_address, server_address;

	listenFD = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons( 8888 );
     
    if( bind(listenFD, (sockaddr *)&server_address, sizeof(server_address)) < 0){
        printf("bind error");
        return 1;
    }

    listen(listenFD, 20);

    len = sizeof(sockaddr_in);
    while( connectFD = accept(listenFD, (sockaddr*)client_address, &len) ){
        char cli_addr[200];
        //inet_ntop(AF_INET, &(sa.sin_addr), str, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(client_address->sin_addr), cli_addr, INET_ADDRSTRLEN);
        printf("Connect from %s %d\n", cli_addr, client_address->sin_port);
    	if(pthread_create(&tid, NULL, client_connect, (void *)&connectFD )){
    		printf("Thread create error\n");
    		return 1;
    	}
    }

    if (connectFD < 0){
        perror("accept failed");
        return 1;
    }
     
    return 0;

}

void* client_connect(void* connectFD){
    
    int sock = *(int*)connectFD;
    int read_size;
    char *message , client_message[2000];

    //write(sock , message , strlen(message));

    //write(sock , message , strlen(message));
    
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 ){
		client_message[read_size] = '\0';
        write(sock , client_message , strlen(client_message));
		memset(client_message, 0, 2000);
    }
     
    if(read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    }else if(read_size == -1){
        perror("recv failed");
    }
         
    return 0;
} 