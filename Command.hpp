#pragma once
#include "Server.hpp"
#include "Client.hpp"

class Server;

class Command
{
private:
	
public:
	Command(/* args */);
	~Command();
    bool checkCommand(char *str, int _socket, Server serv);
};
