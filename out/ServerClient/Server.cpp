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

int main()
{

    int socked, new_fd;
    struct addrinfo hints{}, *serv_info, *p;
    struct sockaddr_storage client_addr{}; // client address information
    socklen_t size;
    struct sigaction sa{};
    int flag = 1;
    char buff[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0 , sizeof hints);

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if((rv = getaddrinfo(nullptr, PORT, &hints, &serv_info)) != 0)
    {
        fprintf(stderr, " GetAddrInfo: %s \n", gai_strerror(rv));
        return 1;
    }
    else
        fprintf(stderr, " GetAddrInfo - Successful!\n");


    // loop through all the results and bind to the first we can
    for(p = serv_info; p != nullptr; p = p->ai_next) {
        if ((socked = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(socked, SOL_SOCKET, SO_REUSEADDR, &flag,
                       sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(socked, p->ai_addr, p->ai_addrlen) == -1) {
            close(socked);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(serv_info); // all done with this structure

    if (p == nullptr)  {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }
    if(listen(socked,BACKLOG) == -1)
    {
        perror("Listen error");
        exit(1);
    }
    else
        fprintf(stderr, "listen SUCCESS\n");

    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if(sigaction(SIGCHLD,&sa, nullptr) == -1)
    {
        perror("sigaction!");
        exit(1);
    }
    else
        fprintf(stderr, "sigaction SUCCESS\n");

    printf("server: waiting for connections...\n");

    while(1)
    {
        size = sizeof client_addr;
        new_fd = accept(socked, (struct sockaddr *) &client_addr,&size);

        if(new_fd == -1)
        {
            perror("accept");
            continue;
        }
        else
        {
            fprintf(stderr, "accept SUCCESS\n");
        }

        inet_ntop(client_addr.ss_family,
            get_in_addr((struct sockaddr*)&client_addr),
                    buff, sizeof buff
        );

        fprintf(stderr, "connection SUCCESS\n");

        if(!fork())
        {
            close(socked);
            if(send(new_fd, "welcome!", 9,0) == -1)
                perror("send");
            else
                fprintf(stderr, "send SUCCESS\n");
            close(new_fd);
            exit(0);

        }
        close(new_fd);

    }
    return 0;

}