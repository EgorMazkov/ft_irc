#include "server.hpp"

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
        std::string pass = av[2];
        Server serv(port, pass);
        // serv.srartServer();
    }
    catch(const char* s)
    {
        std::cout << s << std::endl;
    }
    
}