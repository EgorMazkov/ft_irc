#include "Channel.hpp"
#include "Server.hpp"
#include "Client.hpp"

Channel::Channel(): numClient(0){}

void Channel::setChannel(std::string nameChannel) {
    this->Channels = nameChannel;
}

void Channel::setClients(int _socketClient) {
    this->clients[numClient] = _socketClient;
    this->numClient++;
}

int Channel::socketClientForChannel(int i){return (this->clients[i]);}

int Channel::getNumClient(){return (this->numClient);}

void Channel::setPassword(std::string passwordChannel) {
    this->Password = passwordChannel;
}

void Channel::setAdminChannel(std::string name) {
    this->adminChannel = name;
}

std::string Channel::getChannel() {
    return (this->Channels);
}

Channel::~Channel(){}

void Server::join(int _socket, std::string av1, std::string av2, std::string av3, int flag) {
    int i = 1;
    int q = 2;
    chann = chan.find(av1);
    if (chann != chan.end())
    {
        chan[av1]->setClients(mapa[_socket]->getId());
        std::cout << mapa[_socket]->getNickName() << " added to channel: " << chan[av1]->getChannel() << std::endl;
//        std::cout << "Клиент добавлен\n";
        return;
    }
    else if (numberChannelPasswordChannel >= 0) {
        chan.insert(std::make_pair(av1, new Channel()));
        chan[av1]->setChannel(av1);
        chan[av1]->setPassword(av1);
        chan[av1]->setAdminChannel(mapa[_socket]->getNickName());
        chan[av1]->setClients(mapa[_socket]->getId());
        std::cout << "Channel created. Admin: " + mapa[_socket]->getNickName();
        numberChannelPasswordChannel++;
        return;
    
    }
}

void Server::privmsgChannel(std::string *msg) {
   std::string masseg;
   char m[BUFFER_SIZE];

   int i = 2;
   while (!msg[i].empty()){
       masseg += msg[i] + " ";
       i++;
   }
   strcpy(m, masseg.c_str());
   while (i != chan[msg[1]]->getNumClient()) {
       send(chan[msg[1]]->socketClientForChannel(i), m, strlen(m), 1);
       i++;
   }
}