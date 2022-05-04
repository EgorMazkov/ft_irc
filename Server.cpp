#include "Server.hpp"


Server::Server()
{
};

Server::~Server(){};

bool Server::checkPassword(std::string pass) {
    if (pass == passwordServer)
        return (true);
    return (false);
}

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
	allClients = -1;
	strcpy(buffer, "Hello peer");
	flag = 0;
	numberChannelPasswordChannel = 0;
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
		if (allClients == 99)
		{
			std::cout << "Error: maximum number of clients connected" << std::endl;
			while (allClients == 99)
			{
				checkTerminal(new_socket);
				/*if (если кто-то отключится)
					allClients--; */
			}
		}
		if (new_socket[allClients] != -1)
			allClients++;
		FD_ZERO(&fd_read);
		FD_SET(socket1, &fd_read);
		FD_SET(socket2, &fd_write);
        if (max_fd < socket1)
            max_fd = socket1;
		if (select(max_fd + 1, &fd_read, &fd_write, NULL, &tv) > 0)
        {
			std::pair<int, std::string> pair = connect();
			new_socket[allClients] = pair.first;
			if (new_socket[allClients] != -1)
			{
				fcntl(new_socket[allClients], F_SETFL, O_NONBLOCK);
                cl = mapa.find(new_socket[i]);
                if (cl == mapa.end())
                    mapa.insert(std::make_pair(new_socket[allClients], new Client(new_socket[allClients])));
                flag = 1;
			}
		}
        if (!mapa.empty())
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
    std::cout << new_socket[i] << std::endl;
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
        if (select(max_fd + 1, &fd_read, &fd_write, NULL, &tv) > 0)
        {
    
            res = recv(_new_socket[idClient], str, BUFFER_SIZE, 0);
            if (res > 0)
            {
                if (str[res - 1] == '\n')
                    checkCommand(str, new_socket[idClient], idClient);
            }
            if (mapa[new_socket[idClient]]->getnickCheck() == 1 \
            && mapa[new_socket[idClient]]->getpassCheck() == 1 \
            && mapa[new_socket[idClient]]->getuserCheck() == 1 \
            && mapa[new_socket[idClient]]->getOffineOnline() == 0)
                {
                    mapa[new_socket[idClient]]->setRegisted();
                    mapa[new_socket[idClient]]->setOfflineOnlinePlus();
                    if (mapa[new_socket[idClient]]->getRegisted() != 1)
                        std::cout << mapa[new_socket[idClient]]->getNickName() << " Welcome back\n";
                    else
                        std::cout << mapa[new_socket[idClient]]->getNickName() << " Registed\n";
                    int i = 1;
                    while (i < 4)
                    {
                        motdText(mapa[new_socket[idClient]]->getNickName(), i);
                        send(new_socket[idClient], mot, strlen(mot), 0);
//                        std::cout << mot;
                        // flag = 0;
                        i++;
                    }
                }
                else if (mapa[new_socket[idClient]]->getpassCheck() == 0 \
                && mapa[new_socket[idClient]]->getnickCheck() == 1 \
                && mapa[new_socket[idClient]]->getuserCheck() == 1)
                {
                    std::cout << mapa[new_socket[idClient]]->getNickName() << " not Registed\n";
                    flag = 0;
                    close(new_socket[idClient]);
                    allClients--;
                    delete mapa[new_socket[idClient]];
                }
            idClient++;
        }
        
	}
}

void Server::motdText(std::string nick, int i) {
    std::string Motd;
    
    if (i == 1){
        Motd = "375 " + nick + " :- " + SERVER_IP + " Message of the day - \n";
        strcpy(mot, Motd.c_str());
        return;
    }
    if (i == 2){
        Motd = "372 " + nick + " :- " + buffer + "\n";
        strcpy(mot, Motd.c_str());
        return;
    }
    if (i == 3){
        Motd = "376 " + nick + " :- " + "END of /MOTD command\n";
        strcpy(mot, Motd.c_str());
        return;
    }
}

int Server::strq(char strq[BUFFER_SIZE])
{
    int i = 0;
    while (strq[i] != '\n')
        i++;
    return (i);
}



