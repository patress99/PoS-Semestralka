// CREDIT https://www.youtube.com/watch?v=OSwutjvNjK4&fbclid=IwAR22EkUU9j1yGgXGYZJqERPBUjZdBo5yoA3g6SIhE9Afv-Rb6c0V84Hz1Y0&ab_channel=CodingMadeEasy
#include<SFML/Network.hpp>
#include<string>
#include<iostream>

using namespace std;

int main() {

    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    char connType;
    char buffer[2000];

    size_t received;
    string text = "Connected to: ";

    cout << "Enter (s) for Server, (c) for client: " << endl;

    cin >> connType;

    if (connType == 's') {
        sf::TcpListener listener;
        listener.listen(25565);
        listener.accept(socket);
        text+= "Server";
    } else if (connType == 'c') {
        socket.connect(ip,25565);
        text += "Client";
    }

    socket.send(text.c_str(),text.length() + 1);
    socket.receive(buffer, sizeof(buffer), received);

    cout << buffer << endl;

    system("pause");

    return 0;
}