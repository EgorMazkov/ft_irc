#include "passwd.hpp"

int main(int ac, char **av)
{
    try
    {
        passwd portAndPassword(av[1], av[2]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}