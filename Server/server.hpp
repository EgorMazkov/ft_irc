#pragma once
#include <string>
#include <iostream>
#include <list>
#include <unistd.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define BUFFER_SIZE 512

class Server
{
private:
    int port;
    std::string password;
public:




    Server(int _port, std::string _passwd);
    void initialize(int _port, std::string& _passwd);
    void srartServer();
    Server();
    ~Server();


};
