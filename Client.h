
class Client {

private:

    sf::TcpSocket socket;

public:
    Client(sf::TcpSocket& socket);
    ~Client();

    sf::TcpSocket& getSocket();

};



