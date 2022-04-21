#include "Client.hpp"

Client::Client(int _socket_fd): socket_fd(_socket_fd), id(numberClient++)
{}


void Client::getHost(std::string _Host) {this->Host = _Host;}


Client::~Client(){}