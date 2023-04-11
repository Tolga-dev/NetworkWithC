#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <csignal>
#include <netdb.h> // for getnameinfo()
#include <sstream>

#define MAX_BUFFER 512

#define PORT "3490" // the port client will be connecting to

#define MAXDATASIZE 100 // max number of bytes we can get at once

#define BACKLOG 10   // how many pending connections queue will hold

void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, nullptr, WNOHANG) > 0);

    errno = saved_errno;
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char* argv[])
{

    int socked, size_curr_buff;
    char buff[INET6_ADDRSTRLEN];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    if(argc != 2)
    {
        fprintf(stderr, " Usage: client hostname \n");
        exit(1);
    }
    else
    {
        fprintf(stderr, " Instructions true! \n");
    }
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, " GetAddr info error! enter true thing! \n");
        exit(1);
    }
    else
    {
        fprintf(stderr, " GetAddr info success! \n");
    }

    for(p = servinfo; p != nullptr; p = p->ai_next) {
        if ((socked = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(socked, p->ai_addr, p->ai_addrlen) == -1) {
            close(socked);
            perror("client: connect");
            continue;
        }
        break;
    }

    if(p == nullptr)
    {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }
    else
        fprintf(stderr, "client:  connected! \n");

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
              s, sizeof s);
    printf("client: connecting to %s\n", s);
    freeaddrinfo(servinfo);

    if((size_curr_buff = recv(socked,buff, MAXDATASIZE-1,0)) == -1)
    {
        perror("client: recv! \n");
        exit(1);
    }

    buff[size_curr_buff] = '\0';

    printf("client recv : %s " , buff);

    close(socked);

    return 0;

}