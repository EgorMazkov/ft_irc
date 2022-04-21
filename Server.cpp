#include "Server.hpp"
#include "Client.hpp"


Server::Server()
{
};

Server::~Server(){};

void Server::initial(char **av)
{
	int portmin;
	portmin = atoi(av[1]);
	this->passwordServer = static_cast<std::string>(av[2]);
	this->portServer = portmin;
}


int	Server::getPortServer(void) const
{
	return (this->portServer);
}

int Server::startServer(int ac, char **av)
{
	initial(av);
	client[numberClient] = socket(AF_INET, SOCK_STREAM, 0);
	if (client[numberClient] < 0)
	{
		std::cout << ERROR_S << "establishing socket error.\n" ;
		return (0); // exit запрещен
	}
	std::cout << "SERVER: Socket for server was succesfully created\n";

	server_adress.sin_port = htons(portServer);
	server_adress.sin_family = AF_INET;
	server_adress.sin_addr.s_addr = htons(INADDR_ANY);

	ret = bind(client[numberClient], reinterpret_cast<struct sockaddr*>(&server_adress), sizeof(server_adress));
	if (ret < 0)
	{
		std::cout << ERROR_S << "binding connection. Socket has already been establishing.\n";
		return (-1);
	}

	size = sizeof(server_adress);
	std::cout << "SERVER: listening clients...\n";
	listen(client[numberClient], 1);

	server = accept(client[numberClient], reinterpret_cast<struct sockaddr*>(&server_adress), &size);
	while (true)
	{
		FD_ZERO(&fd_read);
		FD_ZERO(&fd_write);

		FD_SET(socket1, &fd_read);
		FD_SET(socket2, &fd_write);;

		int sock = socket1 > socket2 ? socket1 : socket2;
		tv.tv_sec = 10;
		tv.tv_usec = 0;

		if (select(sock + 1, &fd_read, &fd_write, NULL, &tv) > 0)
		{
			std::pair<int, std::string> pair = connect();
			new_socket = pair.first;
			fcntl(new_socket, F_SETFL, O_NONBLOCK);
			Client client(new_socket);
			client.getHost(pair.second);
			FD_SET(new_socket, &fd_read);
		}
		else
			std::cout << "ERROR" << std::endl;
	}

	// if (server < 0)
	// 	std::cout << ERROR_S << "Can't accepting client.\n";
	// isExit = false;
	// while (true)
	// {
	// 	strcpy(buffer, "=> Server connected!\n");
	// 	send(server, buffer, BUFFER_SIZE, 0);
	// 	std::cout << "=> Connected to the client #" << numberClient << '\n' << "Enter " << CLIENT_CLOSE_CONNECTION_SYMBOL << " to the end to connection/\n\n";

	// 	std::cout << "Client: ";
	// 	recv(server, buffer, BUFFER_SIZE, 0);
	// 	std::cout << buffer << '\n';
	// 	if (is_client_connection_close(buffer))
	// 		isExit = true;

	// 	while (isExit)
	// 	{
	// 		std::cout << "Server: ";
	// 		std::cin.getline(buffer, BUFFER_SIZE);
	// 		send(server, buffer, BUFFER_SIZE, 0);
	// 		if (is_client_connection_close(buffer))
	// 			break;

	// 		std::cout << "Client: ";
	// 		recv(server, buffer, BUFFER_SIZE, 0);
	// 		std::cout << buffer << '\n';
	// 		if (is_client_connection_close(buffer))
	// 			break;
	// 	}

	// 	std::cout << "\n Goodbye..." << '\n';
	// 	isExit = false;
	// }
	return (1);
}

std::pair<int, std::string> Server::connect()
{
	struct sockaddr_in ClientAddr;
	client_length = sizeof(ClientAddr);
	new_socket = accept(client[numberClient], (struct sockaddr *) &ClientAddr, &client_length);
    if (new_socket < 0) 
	{
    	std::cout << "ERROR on accepting the connection" << std::endl;
        return std::make_pair(-1, nullptr);
    }
	std::cout << "New Client Connected, ip: " << inet_ntoa(ClientAddr.sin_addr)
			<< ", port: " << ntohs(ClientAddr.sin_port) << std::endl;
	return std::make_pair(new_socket, inet_ntoa(ClientAddr.sin_addr));
}

bool Server::is_client_connection_close(const char *msg)
{
	for (int i = 0; i < strlen(msg); i++)
	{
		if (msg[i] == CLIENT_CLOSE_CONNECTION_SYMBOL)
			return (true);
	}
	return (false);
}
