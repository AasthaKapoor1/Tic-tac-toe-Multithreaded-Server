#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <limits.h>

#define MAX 80
#define PORT 8989
#define SA struct sockaddr
#define SERVER_BACKLOG 100  // number of waiting collenction the server allows
#define THREAD_POOL_SIZE 20 // number of threads in the server

pthread_t thread_pool[THREAD_POOL_SIZE];                         // fixed number of threads
pthread_mutex_t lock_current_player = PTHREAD_MUTEX_INITIALIZER; // mutex locks
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;

typedef struct sockaddr_in SA_IN;


using namespace std;

void func(int sockfd)
{
    
    char buff[MAX];
    int n;

    while(true){
        bzero(buff, sizeof(buff));

        cout<<"Enter the string : ";

        n=0;

        while((buff[n++] = getchar()) != '\n');

        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        cout<<"From server : "<<buff;

        if((strncmp(buff, "exit", 4)) == 0){
            cout<<"Client Exit...\n";
            break;
        }
    }
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and verify

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        cout << "Socket creation failed...\n";
        exit(0);
    }
    else
    {
        cout << "Socket successfully created...\n";
    }

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, port
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        cout << "Connection failed with server...\n";
        exit(0);
    }

    else
    {
        cout << "Connected to the server...\n";
    }

    func(sockfd); // function for chat

    close(sockfd); // close the socket

    return 0;
}