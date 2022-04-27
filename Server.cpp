#include "Server.hpp"

Command com;

Server::Server()
{
};

Server::~Server(){};

bool Server::checkPassword(std::string pass) {
    if (pass == passwordServer)
        return (true);
    return (false);
}

// Server& Server::operator=(const Server &rhs)
// {
// 	if (this == &rhs)
// 		return (*this);
// 	passwordServer = rhs.passwordServer;
// 	return (*this);
// }

// Server::Server(const Server &src)
// {
// 	*this = src;
// }

void Server::initial(char **av)
{
	int portmin;
	portmin = atoi(av[1]);
	this->passwordServer = static_cast<std::string>(av[2]);
	this->portServer = portmin;
	numberClient = 0;
    FD_ZERO(&fd_read);
    FD_ZERO(&fd_write);
    tv.tv_sec = 0;
	idClient = 0;
    tv.tv_usec = 0;
	str[0] = 0;
	i = -1;
	strcpy(buffer, "Connected Server\n");
	flag = 0;
}

bool Server::bilding()
{
    int i = 1;
    socket1 = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << socket1 << std::endl;
    if (socket1 < 0)
    {
        std::cout << ERROR_S << "establishing socket error.\n" ;
        return false;
    }
    if (setsockopt(socket1, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(int)) == -1)
    {
        std::cout << ERROR_S << std::endl;
    }
    bzero((char *) &server_adress, sizeof(server_adress));
    server_adress.sin_family = AF_INET;
    server_adress.sin_addr.s_addr = htons(INADDR_ANY);
    server_adress.sin_port = htons(portServer);
    if (bind(socket1, (struct sockaddr*)(&server_adress), sizeof(server_adress)) < 0)
    {
        std::cout << ERROR_S << "binding connection. Socket has already been establishing.\n";
        return false;
    }
    std::cout << "SERVER: Socket for server was succesfully created\n";
    fcntl(socket1, F_SETFL, O_NONBLOCK);
    max_fd = socket1;
    return true;
}

int Server::startServer(int ac, char **av)
{
	initial(av);
    if (!bilding())
        return (-1);
	size = sizeof(server_adress);
	std::cout << "Port: " << portServer << std::endl;
	std::cout << "SERVER: listening clients...\n";
	listen(socket1, 1);
	while (true)
	{
		if (i == 99)
		{
			std::cout << "Error: maximum number of clients connected" << std::endl;
			while (i == 99)
			{
				checkTerminal(new_socket);
				/*if (если кто-то отключится)
					i--; */
			}
		}
		if (new_socket[i] != -1)
			i++;
		FD_ZERO(&fd_read);

		FD_SET(socket1, &fd_read);
		FD_SET(socket2, &fd_write);
        if (max_fd < socket1)
            max_fd = socket1;
		if (select(max_fd + 1, &fd_read, &fd_write, NULL, &tv) > 0)
        {
			std::pair<int, std::string> pair = connect();
			new_socket[i] = pair.first;
			if (new_socket[i] != -1)
			{
				fcntl(new_socket[i], F_SETFL, O_NONBLOCK);
				mapa.insert(std::make_pair(new_socket[i], new Client(new_socket[i])));
				flag = 1;
			}
		}
		checkTerminal(new_socket);
	}
	return (1);
}

std::pair<int, std::string> Server::connect()
{
	struct sockaddr_in ClientAddr;
	std::string qwe = "lsdkjflsdkfjsdf";
	client_length = sizeof(ClientAddr);
	new_socket[i] = accept(socket1, (struct sockaddr *) &ClientAddr, &client_length);
    if (new_socket[i] < 0)
	{
        return std::make_pair(-1, qwe);
    }
	std::cout << "New Client Connected, ip: " << inet_ntoa(ClientAddr.sin_addr)
			<< ", port: " << ntohs(ClientAddr.sin_port) << std::endl;
	return std::make_pair(new_socket[i], inet_ntoa(ClientAddr.sin_addr));
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


void Server::checkTerminal(int *_new_socket)
{
	int res;
	idClient = 0;
	while (new_socket[idClient] > 0)
	{
		res = recv(_new_socket[idClient], str, BUFFER_SIZE, 0);
		if (res > 0)
		{
			std::cout << str << std::endl;
			if (str[res - 1] == '\n')
                checkCommand(str, new_socket[idClient]);
		}
		else
		{
			if (flag == 1)
			{
				if (mapa[new_socket[idClient]]->getnickCheck() == 1 \
				&& mapa[new_socket[idClient]]->getpassCheck() == 1 \
				&& mapa[new_socket[idClient]]->getuserCheck() == 1)
				{
					mapa[new_socket[idClient]]->setRegisted();
					std::cout << mapa[new_socket[idClient]]->getNickName() << " Registed\n";
				}
			}
			idClient++;
		}
	}
}


bool Server::checkCommand(char *str, int _socket) {
    int i = 0;
    int q = 0;
    int j = 0;
    std::string av0[7];
    while (str[q] != '\n')
    {
        while (str[q] != ' ')
        {
            if ( (str[q] == '\r' || str[q + 1] == '\n') && str[q + 2])
			{
				i++;
				q += 2;
                continue ;
			}
			else if ((str[q] == '\r' || str[q + 1] == '\n') && !str[q + 2])
				break ;
            if (str[q] == ':')
                q++;
            av0[i] += str[q];
            q++;
        }
        i++;
        if (str[q] == '\n')
            break;
        q++;
        continue;
    }
    if (av0[0] == "PASS")
    {
        if (checkPassword(av0[1]) == true)
        {
            mapa[_socket]->setpassCheck();
            return (true);
        }
        return (false);
    }
    if (av0[0] == "NICK"){
        mapa[_socket]->setnickCheck();
        mapa[_socket]->setNickName(av0[1]);
    }
	if (av0[0] == "USER")
	{
		mapa[_socket]->setuserCheck();
		mapa[_socket]->setUserName(av0[1]);
		mapa[_socket]->setzvezda(av0[2]);
		mapa[_socket]->setHostName(av0[3]);
		mapa[_socket]->setRealname(av0[4]);
	}
    return (false);
}