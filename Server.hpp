#pragma once

#define BUFSIZ 4096

#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>

#define DEFAULT_PORT	1616
#define ERROR_S			"SERVER ERROR: "
#define BUFFER_SIZE		1024
#define CLIENT_CLOSE_CONNECTION_SYMBOL	'#'

class Server
{
	private:
		short portServer;
		const std::string passwordServer;
	public:
		Server(short port, std::string password);
		~Server();
		// Server(Server const &src);

		// Server &operator=(Server const &rhs);
		
		int		getPortServer(void) const;

		
};
