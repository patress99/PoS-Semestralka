// CREDIT https://www.youtube.com/watch?v=OSwutjvNjK4&fbclid=IwAR22EkUU9j1yGgXGYZJqERPBUjZdBo5yoA3g6SIhE9Afv-Rb6c0V84Hz1Y0&ab_channel=CodingMadeEasy
#include<SFML/Network.hpp>
#include<string>
#include<iostream>

using namespace std;

const int PORT = 25565;

int client() {

    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    char connType;
    char buffer[2000];

    size_t received;

    socket.connect(ip,PORT);

    system("pause");

    return 0;
}