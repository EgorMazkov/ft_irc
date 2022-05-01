#include "Client.hpp"

Client::Client(){}

Client::Client(int _socket_fd): socket_fd(_socket_fd), id(++numberClient), passCheck(0), userCheck(0), nickCheck(0), nickname(""), Registed(0), offlineOnline(0)
{std::cout << "Client №" << id << " connected\n";}
void	Client::setRegisted(){++this->Registed;}
void    Client::setuserCheck(){   ++this->userCheck;}
void    Client::setnickCheck(){   ++this->nickCheck;}
void    Client::setpassCheck(){   ++this->passCheck;}
int     Client::getRegisted() {return this->Registed;}
int		Client::getnickCheck(){return(this->nickCheck);}
int		Client::getpassCheck(){return (this->passCheck);}
int		Client::getuserCheck(){return (this->userCheck);}
std::string     Client::getNickName(){return (this->nickname);}
void    Client::setzvezda(std::string str){this->zvezda = str;}
void    Client::setRealname(std::string str){this->Realname = str;}
void    Client::setUserName(std::string str){this->UserName = str;}
void    Client::setHostName(std::string str){this->HostName = str;}
void    Client::setNickName(std::string nick){this->nickname = nick;}
void    Client::setOfflineOnlinePlus() {++this->offlineOnline;}
int     Client::getOffineOnline() {return (this->offlineOnline);}
void    Client::setOfflineOnlineMinus() {--this->offlineOnline;}
int    Client::getId() {return (this->id);}

void Client::setRealNamePlus(std::string str) {
    this->Realname += ' ';
    this->Realname += str;
}

Client::~Client(){}