#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> // for getnameinfo()
#define MAX_BUFFER 512

int main()
{

    struct addrinfo hints, *res;
    int sockfd;
    char buf[512];
    int byte_count;

// get host info, make socket, and connect it
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo("www.example.com", "443", &hints, &res);

    std::cout << "get info" << std::endl;
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    std::cout << "get socket" << std::endl;

    connect(sockfd, res->ai_addr, res->ai_addrlen);
    std::cout << "get connect" << std::endl;

    byte_count = recv(sockfd, buf, sizeof buf, 0);
    std::cout << "get recv" << std::endl;

    printf("recv()'d %d bytes of data in buf\n", byte_count);




};