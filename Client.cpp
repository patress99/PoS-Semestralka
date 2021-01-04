#include<SFML/Network.hpp>
#include<string>
#include<iostream>
#include "Client.h"


using namespace std;

const int PORT = 10022;

Client::Client(sf::TcpSocket& socket) {
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();

    char connType;
    char buffer[2000];

    size_t received;

    socket.connect(ip,PORT);

    system("pause");

}

Client::~Client() {

}


sf::TcpSocket& Client::getSocket() {
    return this->socket;
}