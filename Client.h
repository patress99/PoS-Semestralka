
class Client {

private:

    sf::TcpSocket socket;
    sf::IpAddress ip;
    int port;

public:
    Client(int port);
    ~Client();

    sf::TcpSocket& getSocket();
    sf::IpAddress getIp();

    void tryToConnect();
};



