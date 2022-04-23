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
#include <fcntl.h>

#define ERROR_S			"SERVER ERROR: "
#define BUFFER_SIZE		1024
#define CLIENT_CLOSE_CONNECTION_SYMBOL	'#'
#define SERVER_CLOSE_CONNECTION_SYMBOL	'#'
#define SERVER_IP "127.0.0.1"

// using namespace std;


static int numberClient;

class Server
{
	private:
		short portServer;
		std::string passwordServer, message; 
		socklen_t client_length;

	public:
		/*  переменные который были в main*/
		int				client[100];
		int				server;
		int				ret;
		bool			isExit;
		socklen_t		size;
		Server			*serv;
		struct sockaddr_in	server_adress;
		char			buffer[BUFFER_SIZE]; // отсюда берет текст для клиента
		char			*str; // сюда записываются от клиента информация
		fd_set			fd_read, fd_write;
		struct timeval tv;
		int				new_socket;

		int	socket1, socket2;



		/**/
		Server();
		~Server();
		// Server(Server const &src);

		// Server &operator=(Server const &rhs);
		
		int		getPortServer(void) const;
		int	startServer(int ac, char **av);
		bool is_client_connection_close(const char *msg);
		void	init(std::string port, std::string password);
		void	initial(char **av);
		std::pair<int, std::string> connect();
		bool checkTerminal(int _new_socket);
};
