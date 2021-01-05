
#include "Server.h"


using namespace std;



Server::Server(int port) {
    this->ip = sf::IpAddress::getLocalAddress();
    this->port = port;



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
    listener.listen(this->port);
    listener.accept(this->socket);
    this->socket.connect(this->ip,this->port);
}


