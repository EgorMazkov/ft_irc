#include "Bot.hpp"

Bot::Bot(std::string port, std::string pass):
		 port(port), _pass(pass) { 
	sockaddr_in setter;
	setter.sin_family = AF_INET;
	setter.sin_port = htons(std::atoi(port.c_str()));
	if (inet_aton("127.0.0.1", &setter.sin_addr) == 0)
	{

		std::cout<<"Incorrect ip address has been passed\n\0";
		exit(1);
	}
	if ((serverFd = socket(setter.sin_family, SOCK_STREAM, 0)) == -1)
	{
		std::cout<<"Socket troubles\n\0";
		exit(1);
	}
	if (connect(serverFd, (sockaddr*)&setter, sizeof(setter)) == -1)
	{
		std::cout<<"cannot connect to server\n\0";
		exit(1);
	}
	fcntl(serverFd, F_SETFL, O_NONBLOCK);
	isPass = false;
}

void Bot::start(){
	sender = "PASS " + _pass + "\r\n"\
	"USER 1 1 1 1\r\n"\
	"NICK " + "bot";
	char buff[BUFFER_SIZE];
    while (true)
	{
		if (!sender.empty())
		{
		sender.append("\n");
		send(serverFd, sender.c_str(), strlen(sender.c_str()), 0);
		sender.clear();
		}
		Bytes = 0;
		memset(&buff, 0,sizeof(buff));
		if ((Bytes = recv(serverFd, &buff, BUFFER_SIZE - 1, 0)) >= 0)
		another_buf += buff;
		if (Bytes == 0)
		{
			std::cout << "server is not available!\n\0";
			exit(1);
		}
		check_message();
		sendToServ();
	}     
}

std::string Bot::getRequest() {
	std::string::size_type index = another_buf.find("\n") + 1;
	std::string request = another_buf.substr(0, index);
	another_buf.erase(0, index);
	return request;
}

void Bot::check_message() {
	request = getRequest();
	if (request.find("PRIVMSG") != std::string::npos || request.find("NOTICE") != std::string::npos)
		stringFlag = "PRIVMSG";
	else if (request.find(":IRC 376 bot :End of /MOTD command") != std::string::npos)
	{
		isPass = true;
		std::cout << "Connection to server is successful" << std::endl;
		stringFlag = "NOTHING";
	}
	else if (request.find("PING") != std::string::npos)
	{
		stringFlag = "PONG";
	} 
	else
		stringFlag = "NOTHING";
}

void Bot::sendToServ()
{
	if (stringFlag == "NOTHING")
		return;
	else if (stringFlag == "PONG")
		sender = "PONG ircserv";
	else
	{
		request.erase(0, request.find(":") + 1);
		std::string name = request.substr(0, request.find(" "));
		request.erase(0, request.find(":") + 1);
		std::string req = request.substr(0, request.find("\r"));
		if (req.find("?"))
		{
			struct timeval rTime;
			gettimeofday(&rTime, NULL);
			long int ms = rTime.tv_sec * 1000 + rTime.tv_usec / 1000;
			unsigned int result = ms % 3;
			std::string trueName;
			trueName = name.substr(0, name.find("!"));
			if (result > 1)
				sender = "PRIVMSG " + trueName + " :Yes";
			else
				sender = "PRIVMSG " + trueName + " :No";
		}
	}
}
