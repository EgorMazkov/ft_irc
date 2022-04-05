#include "Server/server.hpp"

int main(int ac, char **av)
{
    if (ac < 3)
    {
        std::cout << "./ircserver <port> <password" << std::endl;
        return 1;
    }
    try
    {
        int port = atoi(av[1]);
        Server serv(port, av[2]);
        serv.srartServer();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}