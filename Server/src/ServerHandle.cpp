#include "ServerHandle.h"
#include "ErrorHandle.h"
#include <sys/socket.h>

using namespace std;



void ServerHandle::Make_BroadCast()
{
    cout << " hello world 0" << endl;
}

void ServerHandle::Make_Request()
{


}


void ServerHandle::SetName()
{

}

template<typename T>
T ServerHandle::CreateSocket()
{
    if((this->Server_Socket = socket(AF_INET,SOCK_STREAM,0))== -1)
        handle_error("Socket");
    else
        fprintf(stderr,"Socket Created!");
    return nullptr;
}

template<typename T>
T ServerHandle::SetBind(struct sockaddr * serv) {

    if((bind(this->Server_Socket,(struct sockaddr *)&serv,sizeof(struct sockaddr_in)))==-1)
        handle_error("Bind");
    else
        fprintf(stderr,"Bound!");
    return nullptr;
}

template<typename T>
T ServerHandle::ListenRequest() {

    if((listen(this->Server_Socket,BACK_LOG))==-1)
        handle_error("Listen!");
    else
        fprintf(stderr,"Listening!");

    return nullptr;
}

template<typename T>
T ServerHandle::GetSocketValue() {
    return this->Server_Socket;
}





