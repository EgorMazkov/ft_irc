#include "Client.hpp"

Client::Client(){}

Client::Client(int _socket_fd): socket_fd(_socket_fd), id(++numberClient)
{

	std::cout << "Client №" << numberClient << " connected\n";
}


void Client::getHost(std::string _Host) {this->Host = _Host;}

void Client::getNickName(std::string nick)
{
	this->nickname = nick;
	std::cout << "NICK client: " << nickname << std::endl;
}


Client::~Client(){}