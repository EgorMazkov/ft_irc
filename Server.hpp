#pragma once

#define BUFSIZ 4096

#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <iostream>


class Server
{
	private:
		const std::string portServer;
		const std::string passwordServer;
	public:
		Server(std::string port, std::string password);
		~Server();
};
