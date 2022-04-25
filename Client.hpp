#pragma once
#include "Server.hpp"
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>


class Client
{
private:
	int		id; // unique id for every user for ping-pong commands
	int     socket_fd; // unique socket for every user for send message from server
    std::string Host;
    std::string nickname;
public:
	Client(int _socket_fd);
	Client();
	void getHost(std::string _host);
	~Client();
	void getNickName(std::string nick);
};

