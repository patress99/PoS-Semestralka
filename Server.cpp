
#include "Server.h"


using namespace std;



Server::Server(int port) {
    this->ip = sf::IpAddress::getLocalAddress();
    this->port = port;
    std::cout << &this->socket<< std::endl;
    std::cout << this->socket.getRemotePort() << std::endl;
    std::cout << this->socket.getRemoteAddress()<< std::endl;

    listener.listen(this->port);
    listener.accept(socket);

    std::cout << "Server sa spojil" << std::endl;

    std::cout << &this->socket<< std::endl;
    std::cout << this->socket.getRemotePort() << std::endl;
    std::cout << this->socket.getRemoteAddress()<< std::endl;
}

Server::~Server() {

}




sf::TcpSocket& Server::getSocket() {
    return this->socket;
}

sf::IpAddress Server::getIp() {
    return this->ip;
}

void Server::listenToConnection() {

}


