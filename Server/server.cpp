#include "server.hpp"
#include "../Command/Command.hpp"
char	**ft_split (char const *s, char c);

Command comm;

Server::Server()
{
}

Server::Server(int _port, std::string _passwd): port(_port), password(_passwd)
{
    if (_port < 1024 || _port > 49151)
        throw "wrong prot";
    std::cout << "Server Done: port: " << _port << std::endl;
}

Server::~Server(){}