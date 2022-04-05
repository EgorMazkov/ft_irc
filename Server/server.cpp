#include "server.hpp"
#include "../Command/Command.hpp"
char	**ft_split (char const *s, char c);

Command comm;

bool Server::checkPassword(std::string passwd)
{
    if (passwd == pass)
        return (false);
    return (true);
}

Server::Server()
{
}

Server::Server(int _port, std::string _passwd)
{
    if (_port < 1024 || _port > 49151)
        throw "wrong prot";
    initialize(_port, _passwd);
    std::cout << "Server Done: port " << _port << std::endl;
}

void Server::initialize(int _port, std::string& _passwd)
{
    port = _port;
    pass = _passwd;
    FD_ZERO(&fdAcc);
    FD_ZERO(&fdRead);
    FD_ZERO(&fdWrite);
}

void Server::srartServer()
{
    char **str;
    std::string qwe;
    while (1)
    {
        std::cin >> **str;
        int i = 0;
        while (str[i])
        {
            std::cout << str[i] << std::endl;
            i++;
        }
        while (1);
        // if (str == "PASS")
        //     comm.passCommand(str[0], str[1]);
    }
}






Server::~Server(){}