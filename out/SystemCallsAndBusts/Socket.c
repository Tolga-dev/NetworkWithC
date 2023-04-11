#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

/*
int serverSocket = socket(
        AF_INET,      // Domain: specifies protocol family
        SOCK_STREAM,  // Type: specifies communication semantics
        0             // Protocol: 0 because there is a single protocol for the specified family
);
*/

int main()
{
    struct addrinfo Manager, *result, *temp = NULL;
    int status;
    char buf[INET_ADDRSTRLEN];

    memset(&Manager,0, sizeof Manager);
    Manager.ai_family = AF_UNSPEC;
    Manager.ai_socktype = SOCK_STREAM;

    const char* server = "www.examp8le.com";
    if ((status = getaddrinfo(server, NULL, &Manager, &result)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }


    if ((status = socket(result->ai_family, result->ai_socktype, result->ai_protocol)== -1))
    {
        fprintf(stderr, "file descriptor error: %s\n", gai_strerror(status));
        return -1;
    }


    freeaddrinfo(result);
    freeaddrinfo(temp);
}