#pragma once
#include <string>
#include <iostream>
#include <list>
#include <unistd.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>

class Server
{
private:
    int port;
    std::string pass;
    fd_set fdAcc, fdRead, fdWrite;
public:

    static uint64_t response_timeout;
    static uint64_t request_timeout;



    Server(int _port, std::string _passwd);
    void initialize(int _port, std::string& _passwd);
    void srartServer();
    bool checkPassword(std::string passwd);
    Server();
    ~Server();
};
