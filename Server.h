#include<SFML/Network.hpp>
#include<string>
#include<iostream>

class Server {

private:

    sf::TcpSocket socket;

public:

    Server(sf::TcpSocket& socket);
    ~Server();

    sf::TcpSocket& getSocket();

};



