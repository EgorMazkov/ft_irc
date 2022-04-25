#pragma once
#include "Server.hpp"
#include "Client.hpp"

class Command
{
private:
	
public:
	Command(/* args */);
	~Command();
    bool checkCommand(char *str);
};
