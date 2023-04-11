#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>


int main()
{
    struct addrinfo provider, *result;
    int sock_curr;
    int status;
//    const char * address = "www.example.com";
    memset(&provider,0,sizeof provider);
    provider.ai_family = AF_UNSPEC; // ipv4 or ipv6
    provider.ai_socktype = SOCK_STREAM;
    provider.ai_flags = AI_PASSIVE; // fill in my ip for me


    if ((status = getaddrinfo(nullptr,"8989", &provider,&result)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }

    sock_curr = socket(result->ai_family,result->ai_socktype,result->ai_protocol);

    if(bind(sock_curr,result->ai_addr,result->ai_addrlen) == -1)
    {
        fprintf(stderr, "bind: -1\n");
        return -1;

    }

    freeaddrinfo(result); // free the linked list



}