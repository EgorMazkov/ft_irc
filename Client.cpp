#include "Client.hpp"

Client::Client(){}

Client::Client(int _socket_fd): socket_fd(_socket_fd), id(++numberClient), passCheck(0), userCheck(0), nickCheck(0), nickname("")
{

	std::cout << "Client №" << id << " connected\n";
}

void Client::setNickName(std::string nick)
{
	this->nickname = nick;
	std::cout << "NICK client: " << nickname << std::endl;
}

Client &Client::operator=(Client *e)
{
	if (this == e)
		return (*this);
	return (*this);
}

void    Client::setuserCheck()
{
    ++this->userCheck;
}

void    Client::setnickCheck()
{
    ++this->nickCheck;
}

void    Client::setpassCheck()
{
    ++this->passCheck;
}

void Client::setzvezda(std::string str)
{
	this->zvezda = str;
}

void Client::setRealname(std::string str)
{
	this->Realname = str;
}

void Client::setUserName(std::string str)
{
	this->UserName = str;
}

void Client::setHostName(std::string str)
{
	this->HostName = str;
}

int		Client::getnickCheck()
{
	return(this->nickCheck);
}

int		Client::getpassCheck()
{
	return (this->passCheck);
}

int		Client::getuserCheck()
{
	return (this->userCheck);
}

void	Client::setRegisted()
{
	++this->Registed;
}

std::string Client::getNickName()
{
	return (this->nickname);
}

Client::~Client(){}