#include <bits/stdc++.h>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sstream>
#include "Server/include/ServerHandle.h"
using namespace std;

mutex Print_mtx,Clients_mtx;
int server_socket = 0;
int clients_socket = 0;
ServerHandle<int> serverHandle(server_socket,clients_socket);

int main()
{
    int client_id=0;

    struct sockaddr_in client{};
    vector<Structure> clients;

    size_t size= sizeof(sockaddr_in);
    server_socket = serverHandle.CreateSocket();

    struct sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr.s_addr=INADDR_ANY;
    bzero(&server.sin_zero,0);


    server = serverHandle.SetBind(server);

    serverHandle.ListenRequest();


    while(1)
    {
        clients_socket = serverHandle.AcceptRequest(client,size);
        client_id++;
        thread t(handle_client,clients_socket,client_id,std::ref(clients));
        lock_guard<mutex> guard(Clients_mtx);
        clients.push_back({client_id, string("Server"),clients_socket,(move(t))});
    }

    for(int i=0; i<clients.size(); i++)
    {
        if(clients[i].th.joinable())
            clients[i].th.join();
    }

    close(server_socket);
    return 0;
}

void Share_Common_Text(const string& str)
{
    lock_guard<mutex> guard(Print_mtx);
    serverHandle.Share_Common_Text(str);
}

void Shut_Down_Client(int id,vector<Structure>& clients)
{
    for(int i=0; i<clients.size(); i++)
    {
        if(clients[i].id==id)
        {
            lock_guard<mutex> guard(Clients_mtx);
            clients[i].th.detach();
            clients.erase(clients.begin()+i);
            close(clients[i].socket);
            break;
        }
    }


}

void handle_client(int client_socket, int id,vector<Structure>& clients)
{
    char name[MAX_LEN],str[MAX_LEN];
    recv(client_socket,name,sizeof(name),0);
    serverHandle.SetName(id,name,clients);

    string welcome_message=string(name)+string(" has joined");

    serverHandle.Make_BroadCast(SERVER_MESSAGE,id,clients); // say message from server
    serverHandle.Make_BroadCast(welcome_message,id,clients); // say message
    Share_Common_Text(welcome_message);

    while(1)
    {
        int bytes_received=recv(client_socket,str,sizeof(str),0);
        if(bytes_received<=0)
            return;
        if(strcmp(str,CLIENT_QUIT_MESSAGE)==0)
        {
            string message=string(name)+string(" has left");
            serverHandle.Make_BroadCast(SERVER_MESSAGE,id,clients); // say message from server
            serverHandle.Make_BroadCast(message,id,clients); // say message
            Share_Common_Text(message);
            Shut_Down_Client(id,clients);
            return;
        }
        serverHandle.Make_BroadCast(string(name),id,clients);
        serverHandle.Make_BroadCast(string(str),id,clients);
        Share_Common_Text(string(name)+" : "+str);
    }
}