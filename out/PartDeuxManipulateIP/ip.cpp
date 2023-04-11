#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> // for getnameinfo()
#include <experimental/internet>
using namespace std;
#define MAX_BUFFER 512

/* Structure describing an Internet socket address.  */
namespace SocketStruct
{
    struct sockaddr_in sa; // ipv4
    struct sockaddr_in6 sa6; // ip6
}

void foo()
{
    const char *ip = "10.12.110.57";
    const char *bin_ip = "2001:db8:63b3:1::3490";

    ///convert string IP addresses to their binary representations.
    inet_pton(AF_INET, ip,&(SocketStruct::sa));
    inet_pton(AF_INET6, bin_ip,&(SocketStruct::sa6));

}

int main()
{
    char ip4[INET_ADDRSTRLEN]; // 16
    struct sockaddr_in sa; // ipv4
    inet_ntop(AF_INET,&(sa.sin_addr),ip4,INET_ADDRSTRLEN);
    cout << "ipv4 -> " << ip4 << endl; // 0.0.0.0

    char ip6[INET6_ADDRSTRLEN]; // 46
    struct sockaddr_in6 sa6; // ip6
    inet_ntop(AF_INET6, &(sa6.sin6_addr), ip6, INET6_ADDRSTRLEN);
    cout << "ipv6 -> " << ip6 << endl; // ::

    //ipv4 -> 202.85.0.0
    //ipv6 -> e4a4:d5b0:ca55:0:bf11::


};