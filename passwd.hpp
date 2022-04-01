#pragma once
#include <string>
#include <iostream>
#include <exception>
#include <sstream>

template <typename T>
std::string to_string(T arg){
	std::stringstream ss;
	ss << arg;
	return ss.str();
}

class passwd
{
private:
    int port;
    std::string password;
public:
    passwd(char *portMain, char *passwdMain);
    void CheckPasswdAndPort(char *portMain, char *passwdMain);
    ~passwd();




    // struct NotArguments : public std::exception{
	// 	const int m_nGrade;
	// 	NotArguments(int grade) : m_nGrade(grade){}
	// 	virtual const char *what() const throw()
	// 	{
	// 		std::string a("NotArguments: ");
    //         switch (m_nGrade)
    //         {
    //             case 1:
    //                 a += to_string("port");
    //                 break;
    //             case 2:
    //                 a += to_string("password");
    //                 break;
    //         }
    //         std::cout << a.c_str() << std::endl;
	// 		return a.c_str();
	// 	}
	// };

    struct ErrorForIrc : public std::exception{
        std::string  eMessage;
        ErrorForIrc(std::string message) : eMessage(message){}
        virtual const char *what() const throw()
            {
                std::string a = to_string(eMessage);
                std::cout << a.c_str() << std::endl;
                return a.c_str();
            }
    };
};