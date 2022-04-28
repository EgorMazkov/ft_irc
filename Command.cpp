#include "Server.hpp"


bool Server::checkCommand(char *str, int _socket, int idClient) {
    std::string av0[100];
    int flag = 0;
    int i = 0;
    int q = 0;
    if (str[q] == 'Q')
    {
        while (str[q] != '\n')
            av0[0] += str[q++];
    }
    while (str[q] != '\n')
    {
        while (str[q] != ' ')
        {
            if (str[q] == '\r' || str[q] == ':')
                q++;
            if (str[q] == '\n')
                break ;
            av0[i] += str[q];
            q++;
        }
        i++;
        q++;
        if (!str[q])
            break ;
    }
    q = idClient + 1;
    flag = i;
    i = 0;
    
    while (mapa[_socket]->getRegisted() != 1)
    {
        if (av0[i] == "PASS")
        {
            std::cout << "Client #" << q;
            std::cout << " <" << av0[i] << "> ";
            std::cout << "<" << av0[i + 1] << ">\n";
            if (checkPassword(av0[++i]))
            {
                flag++;
                mapa[_socket]->setpassCheck();
            }
            if (av0[i + 1] == "NICK" || av0[i + 1] == "USER")
                i++;
            else
                return (false);
        }
        if (av0[i] == "NICK"){
            std::cout << "Client #" << q;
            std::cout << " <" << av0[i] << "> ";
            mapa[_socket]->setnickCheck();
            mapa[_socket]->setNickName(av0[++i]);
            std::cout << "<" << av0[i] << ">\n";
            flag++;
            if (av0[i + 1] == "PASS" || av0[i + 1] == "USER")
                i++;
            else
                return (false);
        }
        if (av0[i] == "USER")
        {
            std::cout << "Client #" << q;
            std::cout << " <" << av0[i] << "> ";
            mapa[_socket]->setuserCheck();
            mapa[_socket]->setUserName(av0[++i]);
            std::cout << "<" << av0[i] << "> ";
            mapa[_socket]->setzvezda(av0[++i]);
            std::cout << "<" << av0[i] << "> ";
            mapa[_socket]->setHostName(av0[++i]);
            std::cout << "<" << av0[i] << "> ";
            mapa[_socket]->setRealname(av0[++i]);
            std::cout << "<" << av0[i] << "> ";
            i++;
            while (av0[i] != "PASS" || av0[i] != "NICK")
            {
                if (i == flag)
                {
                    std::cout << std::endl;
                    break ;
                }
                if (av0[i] == "NICK" || av0[i] == "PASS")
                {
                    std::cout << std::endl;
                    break ;
                }
                std::cout << "<" << av0[i] << ">\n";
                mapa[_socket]->setRealNamePlus(av0[i]);
                i++;
            }
            flag++;
            if (av0[i] == "PASS" || av0[i] == "NICK")
                continue ;
            else
                return (false);
        }
    }
    if (av0[i] == "QUIT"){quit(_socket);}
//	if (av0[i] == "JOIN"){join(_socket, av0, flag);}
    return (false);
}

void Server::quit(int _socket) {close(_socket);}

//void Server::join(int _socket, std::string *av0, int flag) {
//    int i = numberChannelPasswordChannel;
//    if (numberChannelPasswordChannel != 0)
//    {
//        while (numberChannelPasswordChannel != 0)
//        {
//            if (av0->compare(channel[numberChannelPasswordChannel]))
//
//        }
//    }
//    channel[numberChannelPasswordChannel] = av0[i];
//    std::cout << mapa[_socket]->getNickName() << " created Channel: " << channel[numberChannelPasswordChannel] << "\n";
//    if (i + 1 < flag) {
//        passwordChannel[numberChannelPasswordChannel] = av0[++i];
//        std::cout << "Password: " << passwordChannel[numberChannelPasswordChannel];
//    }
//    std::cout << std::endl;
//    numberChannelPasswordChannel++;
//
//}