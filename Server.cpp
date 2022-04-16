#include "Server.hpp"

Server::Server(short port, std::string password): passwordServer(password), portServer(port) {};

Server::~Server(){};

// Server::Server(Server const &src)
// {
//     *this = src;
// }

// Server  &Server::operator=(Server const &rhs)
// {
//     this->passwordServer = rhs.passwordServer;
//     this->portServer = rhs.portServer;
//     return (*this);
// }

int	Server::getPortServer(void) const
{
	return (this->portServer);
}