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

int main()
{

    int socked;
    struct addrinfo hints{}, *serv_info, *p;
    int rv, curr_buff_size;
    struct sockaddr_storage client_addr{};
    char s[INET6_ADDRSTRLEN];
    char buff[MAX_BUFFER];
    socklen_t  addr_len;

    memset(&hints,0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    if((rv = getaddrinfo(nullptr,PORT,&hints,&serv_info)) != 0)
    {
        fprintf(stderr,"Getaddinfo error: %s", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = serv_info; p != nullptr; p = p->ai_next) {
        if ((socked = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("listener: socket");
            continue;
        }

        if (bind(socked, p->ai_addr, p->ai_addrlen) == -1) {
            close(socked);
            perror("listener: bind");
            continue;
        }

        break;
    }

    if(p== nullptr)
    {
        fprintf(stderr,"listener error!");
        return 1;
    }
    freeaddrinfo(serv_info);

    printf("listener: waiting to recvfrom...\n");

    addr_len = sizeof client_addr;

    if ((curr_buff_size = recvfrom(socked, buff, MAX_BUFFER-1 , 0,
                             (struct sockaddr *)&client_addr, &addr_len)) == -1) {
        perror("recvfrom");
        exit(1);
    }

    printf("listener: got packet from %s\n",
           inet_ntop(client_addr.ss_family,
                     get_in_addr((struct sockaddr *)&client_addr),
                     s, sizeof s));
    printf("listener: packet is %d bytes long\n", curr_buff_size);
    buff[curr_buff_size] = '\0';
    printf("listener: packet contains \"%s\"\n", buff);

    close(socked);


}