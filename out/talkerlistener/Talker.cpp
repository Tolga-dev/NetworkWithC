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

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{

    int socked;
    struct addrinfo hints{}, *serv_info, *p;
    int rv, curr_buff_size;

    if (argc != 3) {
        fprintf(stderr,"usage: talker hostname message\n");
        exit(1);
    }

    memset(&hints,0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    if((rv = getaddrinfo(argv[1],PORT,&hints,&serv_info)) != 0)
    {
        fprintf(stderr,"Getaddinfo error: %s", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and make a socket
    for(p = serv_info; p != nullptr; p = p->ai_next) {
        if ((socked = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("talker: socket");
            continue;
        }

        break;
    }

    if(p== nullptr)
    {
        fprintf(stderr,"talker error!");
        return 1;
    }



    if ((curr_buff_size = sendto(socked, argv[2], strlen(argv[2]), 0,
                           p->ai_addr, p->ai_addrlen)) == -1) {
        perror("talker: sendto");
        exit(1);
    }

    freeaddrinfo(serv_info);

    printf("talker: sent %d bytes to %s\n", curr_buff_size, argv[1]);


    close(socked);


}