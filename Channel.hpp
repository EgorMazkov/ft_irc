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
    int clients[BUFFER_SIZE];
    int     numClient;
    std::string adminChannel;
    std::string message[BUFFER_SIZE];
public:
    Channel();
    void setChannel(std::string nameChannel);
    void setPassword(std::string passwordChannel);
    void setClients(int _socketClient);
    void setAdminChannel(std::string name);
    ~Channel();
    std::string getChannel();
    bool checkChannel(std::string nickChannel);
    int getNumClient();
    int socketClientForChannel(int i);
//    void join(int _socket, std::string av0, std::string av1, std::string av2, int flag);
    
};