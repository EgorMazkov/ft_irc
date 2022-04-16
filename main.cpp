#include "Server.hpp"

bool is_client_connection_close(const char *msg);

int main(int ac, char **av)
{
	int				client;
	int				server;
	int				ret;
	bool			isExit;
	socklen_t		size;
	Server			*serv;
	struct sockaddr_in	server_adress;
	char			buffer[BUFFER_SIZE];

	if (ac != 3)
	{
		std::cout << "gey" << std::endl;
		return (1);
	}
	//printf("%d\n", serv->getPortServer());
	client = socket(AF_INET, SOCK_STREAM, 0);
	if (client < 0)
	{
		std::cout << ERROR_S << "establishing socket error.\n";
		exit (0);
	}
	std::cout << "SERVER: Socket for server was succesfully created\n";

	server_adress.sin_port = htons(DEFAULT_PORT);
	//printf("\n\n\nfddfsfsdff\n\n\n");
	server_adress.sin_family = AF_INET;
	server_adress.sin_addr.s_addr = htons(INADDR_ANY);

	ret = bind(client, reinterpret_cast<struct sockaddr*>(&server_adress), sizeof(server_adress));
	if (ret < 0)
	{
		std::cout << ERROR_S << "binding connection. Socket has already been establishing.\n";
		return (-1);
	}

	size = sizeof(server_adress);
	std::cout << "SERVER: listening clients...\n";
	listen(client, 1);

	server = accept(client, reinterpret_cast<struct sockaddr*>(&server_adress), &size);

	if (server < 0)
		std::cout << ERROR_S << "Can't accepting client.\n";

	isExit = false;
	while (server > 0)
	{
		strcpy(buffer, "=> Server conected!\n");
		send(server, buffer, BUFFER_SIZE, 0);
		std::cout << "=> Conected to the client #1" << '\n' << "Enter " << CLIENT_CLOSE_CONNECTION_SYMBOL << " to the end to connection/\n\n";

		std::cout << "Client: ";
		recv(server, buffer, BUFFER_SIZE, 0);
		std::cout << buffer << '\n';
		if (is_client_connection_close(buffer))
			isExit = true;

		while (isExit)
		{
			std::cout << "Server: ";
			std::cin.getline(buffer, BUFFER_SIZE);
			send(server, buffer, BUFFER_SIZE, 0);
			if (is_client_connection_close(buffer))
				break;

			std::cout << "Client: ";
			recv(server, buffer, BUFFER_SIZE, 0);
			std::cout << buffer << '\n';
			if (is_client_connection_close(buffer))
				break;
		}

		std::cout << "\n Goodbye..." << '\n';
		isExit = false;
		exit (1);
	}
	return (0);
}

bool is_client_connection_close(const char *msg)
{
	for (int i = 0; i < strlen(msg); i++)
	{
		if (msg[i] == CLIENT_CLOSE_CONNECTION_SYMBOL)
			return (true);
	}
	return (false);
}