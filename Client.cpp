#include "Client.hpp"

Client::Client(){}

Client::Client(int _socket_fd): socket_fd(_socket_fd), id(++numberClient), passCheck(0), userCheck(0), nickCheck(0), nickname(strdup(""))
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

Client::~Client(){}