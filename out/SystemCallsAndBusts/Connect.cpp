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
    const char * address = "www.example.com";
    memset(&provider,0,sizeof provider);
    provider.ai_family = AF_UNSPEC; // ipv4 or ipv6
    provider.ai_socktype = SOCK_STREAM;
    provider.ai_flags = AI_PASSIVE; // fill in my ip for me


    if ((status = getaddrinfo(address,"8989", &provider,&result)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }

    sock_curr = socket(result->ai_family,result->ai_socktype,result->ai_protocol);

//    Return 0 on success, -1 for errors.

//    The kernel will choose a local port for us, and the site we connect to will automatically get this information from us.
//    No needed bind
    if ((status = connect(sock_curr,result->ai_addr,result->ai_addrlen)) == -1) {
        fprintf(stderr, "connect: %s\n", gai_strerror(status));
        return 2;
    }

    freeaddrinfo(result); // free the linked list



}