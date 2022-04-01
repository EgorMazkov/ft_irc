#include "passwd.hpp"

passwd::passwd(char *portMain, char *passwdMain)
{
    CheckPasswdAndPort(portMain, passwdMain);
}

void passwd::CheckPasswdAndPort(char *portMain, char *passwdMain)
{

    std::string NotA = "Not Arguments: port";
    // if (portMain == NULL)
    //     throw NotArguments(1);
    // if (!passwdMain)
    //     throw NotArguments(2);
    if (portMain == NULL)
        throw ErrorForIrc(NotA);
    // if (!passwdMain)
        // throw ErrorForIrc("Not Arguments: password");


    std::cout
            << "port " << portMain << std::endl
            << "pass " << passwdMain << std::endl;
}

passwd::~passwd()
{

}

