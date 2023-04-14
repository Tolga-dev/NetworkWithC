#include "../include/ServerHandle.h"
#include "../include/ErrorHandle.h"

template<> int ServerHandle<int>::CreateSocket() {
    if((this->Server_Socket = socket(AF_INET,SOCK_STREAM,0))== -1)
        handle_error("Socket");
    else
        fprintf(stderr,"Socket Created! \n");
    return this->Server_Socket;
}

template<> struct sockaddr_in ServerHandle<int>::SetBind(struct sockaddr_in serv) {

    if((bind(this->Server_Socket,(struct sockaddr *)&serv,sizeof(struct sockaddr_in)))==-1)
        handle_error("Bind");
    else
        fprintf(stderr,"Bound! \n");

    return serv;
}
template<> void ServerHandle<int>::ListenRequest() {

    if((listen(this->Server_Socket,BACK_LOG))==-1)
        handle_error("Listen!");
    else
        fprintf(stderr,"Listening! \n");

}
template<> int ServerHandle<int>::AcceptRequest(struct sockaddr_in client, unsigned int size) {

    if((this->Client_Socket=accept(this->Server_Socket,(struct sockaddr *)&client,&size))==-1)
        handle_error("Accept!");
    else
        fprintf(stderr,"Accepted! \n");
    return this->Client_Socket;
}


template<> void ServerHandle<int>::SetName(int id, char name[],vector<Structure> & clients)
{
    for(auto & client : clients)
        if(client.id==id)
            client.name=string(name);
}


template<> void ServerHandle<int>::Share_Common_Text(const string& shared){
    cout<<shared<<endl;
}

template<> void ServerHandle<int>::Make_BroadCast(const string &something, int sender_id, vector<Structure> &clients) {
    const char *temp = something.c_str();
    for(auto & client : clients)
    {
        if(client.id!=sender_id)
            send(client.socket,temp,sizeof(temp),0);
    }

}











