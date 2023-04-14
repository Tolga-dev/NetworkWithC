//
// Created by xamblot on 4/13/23.
//

#ifndef XSERVER_SERVERHANDLE_H
#define XSERVER_SERVERHANDLE_H

#define BACK_LOG 10
#include <iostream>
/// Todo General Tasks
#include "../include/ErrorHandle.h"
#include <sys/socket.h>
using namespace std;
#include <netinet/in.h>


struct Structure
{
    int id;
    string name;
    int socket;
    thread th;

};


template<class T>
class ServerHandle
{
public:
    explicit ServerHandle(int server_socket,int Client_Socket)
        : Server_Socket(server_socket), Client_Socket(server_socket)

        {};

    ~ServerHandle() = default;

    int CreateSocket();

    struct sockaddr_in SetBind(struct sockaddr_in serv);
    void ListenRequest();
    int AcceptRequest(struct sockaddr_in client, unsigned int size);

    void SetName(int id, char name[],vector<Structure> & clients);
    void Share_Common_Text(const string& shared);

    void Make_BroadCast(const string& something, int sender_id, vector<Structure> &clients);


private:
     int Server_Socket = 0;
     int Client_Socket = 0;

};


void Shut_Down_Client(int id,vector<Structure>& clients);
void handle_client(int client_socket, int id,vector<Structure>& clients);
void Share_Common_Text(const string& str);


#endif //XSERVER_SERVERHANDLE_H
