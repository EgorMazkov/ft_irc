#pragma once

#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/time.h>
#include <iostream>
#include <vector>
#include <list>
#include <fcntl.h>
#include <unistd.h>
#include <map>
#include <sys/time.h>


#define BUFFER_SIZE 1024

class Bot {
private:
	std::string 	_name;
	std::string 	port;
	std::string 	_pass;
	std::string 	sender;
	std::string 	another_buf;
	std::string 	stringFlag;
	std::string 	request;
	bool			isPass;
	int 			serverFd;
	int 			Bytes;
public:
	Bot(std::string, std::string);

	void			start();
	void			check_message();
	void			sendToServ();
	std::string		getRequest();
};