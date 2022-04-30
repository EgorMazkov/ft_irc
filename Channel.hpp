#pragma once
#include "Server.hpp"

class Server;

#define BUFFER_SIZE 1024
static int numberClients;
class Channel
{
private:
    std::string Channels;
    std::string Password;
    std::string clients[BUFFER_SIZE];
    std::string adminChannel;
public:
    Channel();
    void setChannel(std::string nameChannel);
    void setPassword(std::string passwordChannel);
    void setClients(std::string _socketClient);
    void setAdminChannel(std::string name);
    ~Channel();
    bool checkChannel(std::string nickChannel);
//    void join(int _socket, std::string av0, std::string av1, std::string av2, int flag);
    
};