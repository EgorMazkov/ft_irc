#include "Server.hpp"

int main(int ac, char **av)
{

	if (ac != 3)
	{
		std::cout << "gey" << std::endl;
		return (1);
	}
	Server server(std::string(av[1]), std::string(av[2]));
}