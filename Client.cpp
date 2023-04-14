#include <bits/stdc++.h>
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
#include "Server/include/ErrorHandle.h"

#define MAX_BUFFER 200
#define MAX_BUFFER 200

using namespace std;

bool exit_flag=false;
thread t_send, t_recv;

int eraseText(int cnt);
void send_message(int client_socket);
void recv_message(int client_socket);
int client_socket;


int main()
{
    if((client_socket=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        perror("socket: ");
        exit(-1);
    }

    struct sockaddr_in client;
    client.sin_family=AF_INET;
    client.sin_port=htons(PORT); // Port no. of server
    client.sin_addr.s_addr=INADDR_ANY;
    //client.sin_addr.s_addr=inet_addr("127.0.0.1"); // Provide IP address of server
    bzero(&client.sin_zero,0);

    if((connect(client_socket,(struct sockaddr *)&client,sizeof(struct sockaddr_in)))==-1)
    {
        perror("connect: ");
        exit(-1);
    }
    char name[MAX_BUFFER];
    cout<<"Enter your name : ";
    cin.getline(name,MAX_BUFFER);
    send(client_socket,name,sizeof(name),0);


    thread t1(send_message, client_socket);
    thread t2(recv_message, client_socket);

    t_send=move(t1);
    t_recv=move(t2);

    if(t_send.joinable())
        t_send.join();
    if(t_recv.joinable())
        t_recv.join();

    return 0;
}


// Send message to everyone
void send_message(int client_socket)
{
    while(1)
    {
        char str[MAX_BUFFER];
        cin.getline(str,MAX_BUFFER);
        send(client_socket,str,sizeof(str),0);
        if(strcmp(str,CLIENT_QUIT_MESSAGE)==0)
        {
            exit_flag=true;
            t_recv.detach();
            close(client_socket);
            return;
        }
    }
}

// Receive message
void recv_message(int client_socket)
{
    int Message_Anonymous_Sender = 0;
    while(1)
    {
        if(exit_flag)
            return;
        char name[MAX_BUFFER], str[MAX_BUFFER];
        int bytes_received=recv(client_socket,name,sizeof(name),0);
        if(bytes_received<=0)
            continue;
        recv(client_socket,str,sizeof(str),0);
        if(strcmp(name,SERVER_MESSAGE)!=0)
            cout<<name<<" : "<<str<<endl;
        else
            cout<<str<<endl;

        fflush(stdout);
    }
}