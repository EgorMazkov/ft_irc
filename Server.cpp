#include "Server.hpp"

Server serv;

void Server::initial(int portMain, std::string passwordMain)
{
	t_fds fds;
	this->port = portMain;
	this->password = passwordMain;
	std::cout
		<< "port: " << port << std::endl
		<< "pass: " << password << std::endl;
	serv.create(&fds);
	serv.mainLoop(&fds);
}

void Server::create(t_fds *fds)
{
	int s;

	pe = (struct protoent *)Xv(NULL, getprotobyname("tcp"), "getprotobyname");
	s = X(-1, socket(PF_INET, SOCK_STREAM, pe->p_proto), "socket");
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	X(-1, bind(s, (struct sockaddr *)&sin, sizeof(sin)), "bind");
	X(-1, listen(s, 42), "listen");
	fds[s].type = 1;
	srvAccept(fds, s);
}

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << av[0] << " <port> <password>" << std::endl;
		return (1);
	}
	serv.initial(atoi(av[1]), av[2]);
}

int Server::x_int(int err, int res, char *str, char *file, int line)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s, %d): %s\n",
				str, file, line, strerror(errno));
		exit(1);
	}
	return (res);
}

void *Server::x_void(void *err, void *res, char *str, char *file, int line)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s, %d): %s\n",
				str, file, line, strerror(errno));
		exit(1);
	}
	return (res);
}

void Server::srvAccept(t_fds *fds, int s)
{
	int cs;

	csin_len = sizeof(csin);
	cs = X(-1, accept(s, (struct sockaddr *)&csin, &csin_len), "accept");
	std::cout << "New client #%d from %s:%d\n"
			  << cs << inet_ntoa(csin.sin_addr) << ntohs(csin.sin_port) << std::endl;
	cleanFD(&fds[cs]);
	fds[cs].type = 2;
	serv.client_read(fds, cs);
	serv.client_write(fds, cs);
}

void Server::cleanFD(t_fds *fds)
{
	fds->type = 0;
	fds->fctRead = NULL;
	fds->fctWrite = NULL;
}

void Server::client_read(t_fds *fds, int cs)
{
	int r, i;

	r = recv(cs, fds[cs].buffRead, BUFSIZ, 0);
	if (r <= 0)
	{
		close(cs);
		cleanFD(&fds[cs]);
		std::cout << "clien" << cs << "Done away" << std::endl;
	}
	else
	{
		i = 0;
		while (i < maxfd)
		{
			if (fds[i].type == 2 && i != cs)
				send(i, fds[cs].buffRead, r, 0);
			i++;
		}
	}
}

void Server::client_write(t_fds *fds, int cs)
{
	(void)fds;
	(void)cs;
	std::cout << "you gey" << std::endl;
}

void Server::mainLoop(t_fds *fds)
{
	while (1)
	{
		serv.init_fd(fds);
		serv.do_select();
		serv.check_fd(fds);
	}
}

void Server::init_fd(t_fds *fds)
{
	int i;

	i = 0;
	max = 0;
	FD_ZERO(&fdRead);
	FD_ZERO(&fdWrite);
	while (i < maxfd)
	{
		if (fds[i].type != 0)
		{
			FD_SET(i, &fdRead);
			if (strlen(fds[i].buffWrite) > 0)
			{
				FD_SET(i, &fdWrite);
			}
			max = MAX(max, i);
		}
		i++;
	}
}

void Server::do_select()
{
	r = select(max + 1, &fdRead, &fdWrite, NULL, NULL);
}

void Server::check_fd(t_fds *fds)
{
	int i;

	i = 0;
	while ((i < maxfd) && (r > 0))
	{
		if (FD_ISSET(i, &fdRead))
			fds[i].fctRead();
		if (FD_ISSET(i, &fdWrite))
			fds[i].fctWrite();
		if (FD_ISSET(i, &fdRead) ||
			FD_ISSET(i, &fdWrite))
			r--;
		i++;
	}
}
