#include<SFML/Network.hpp>
#include<string>
#include<iostream>

class Server {

private:

    sf::TcpSocket socket;
    sf::IpAddress ip;
    sf::TcpListener listener;

    int port;

public:

    Server(int port);
    ~Server();

    sf::TcpSocket& getSocket();
    sf::IpAddress getIp();


    void listenToConnection();



};



