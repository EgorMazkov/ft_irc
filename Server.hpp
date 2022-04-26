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
#include <map>

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
        std::map<std::string, std::string> mapa;
		int				i;
		int				idClient;
		int				*client;
		int				server;
		int				ret;
		bool			isExit;
		socklen_t		size;
		Server			*serv;
		struct sockaddr_in	server_adress;
		char			buffer[BUFFER_SIZE]; // отсюда берет текст для клиента
		char			str[0]; // сюда записываются от клиента информация
		char			*recv_str;
		fd_set			fd_read, fd_write;
		struct timeval tv;
		int				new_socket[100], previous_socket;

        int max_fd;
		int	socket1, socket2;



		/**/
		Server();
		~Server();
		// Server(Server const &src);

		// Server &operator=(Server const &rhs);
		
		int	startServer(int ac, char **av);
		bool is_client_connection_close(const char *msg);
		void	init(std::string port, std::string password);
		void	initial(char **av);
		std::pair<int, std::string> connect();
		void checkTerminal(int *_new_socket);
        bool bilding();
        bool checkPassword(std::string pass);
};
