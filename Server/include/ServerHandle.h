//
// Created by xamblot on 4/13/23.
//

#ifndef XSERVER_SERVERHANDLE_H
#define XSERVER_SERVERHANDLE_H

#define BACK_LOG 10
#include <iostream>
/// Todo General Tasks

class ServerHandle
{
public:
    explicit ServerHandle(int server_socket) : Server_Socket(server_socket)
    {

    };

    ~ServerHandle() = default;

    void Make_Request();
    void Make_BroadCast();
    void SetName();

    template<typename T>
    T CreateSocket();

    template<typename T>
    T SetBind(struct sockaddr * serv);

    template<typename T>
    T ListenRequest();

    template<typename T>
    T AcceptRequest(struct sockaddr * client, size_t size);

    template<typename T>
    T GetSocketValue();


private:
    unsigned int Server_Socket;

};

template<typename T>
T ServerHandle::AcceptRequest(struct sockaddr *client, size_t size) {
    return nullptr;
}



#endif //XSERVER_SERVERHANDLE_H
