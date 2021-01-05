#include<SFML/Network.hpp>
#include<string>
#include<iostream>
#include "Client.h"


using namespace std;


Client::Client(int port) {
    this->ip = sf::IpAddress::getLocalAddress();
    this->port = port;




}

Client::~Client() {

}


sf::TcpSocket& Client::getSocket() {
    return this->socket;
}

sf::IpAddress Client::getIp() {
    return this->ip;
}

void Client::tryToConnect() {
    this->socket.connect(ip,this->port);
}
