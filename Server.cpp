
#include "Server.h"


using namespace std;

const int PORT = 10022;


Server::Server(sf::TcpSocket& socket) {
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    char connType;
    char buffer[2000];


    size_t received;

    sf::TcpListener listener;
    listener.listen(PORT);
    listener.accept(socket);

    socket.connect(ip,PORT);

    system("pause");

}

Server::~Server() {

}

sf::TcpSocket& Server::getSocket() {
    return this->socket;
}


