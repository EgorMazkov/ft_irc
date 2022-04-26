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
	int		id;
	int     socket_fd;
    std::string nickname;
	int			passCheck;
	int			nickCheck;
	int			userCheck;

	
public:
	Client(int _socket_fd);
	Client();
	~Client();
	void setNickName(std::string nick);
	Client& operator=(Client *e);
	void    setuserCheck();
	void    setnickCheck();
	void    setpassCheck();

};
