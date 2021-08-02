#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

int main() {
    sf::UdpSocket socket;
    unsigned short broadcasting_port = 52000;

    sf::IpAddress address = sf::IpAddress::Broadcast;

    std::cout << "What do you want to become? s for server and c for client."
              << std::endl;
    char ans;
    std::cin >> ans;
    if (ans == 's') {
        sf::Packet packet;

        packet << sf::IpAddress::getLocalAddress().toString();
        if (socket.send(packet, address, broadcasting_port) !=
            sf::Socket::Done) {
            std::cout << "Error while broadcasting" << std::endl;
            exit(1);
        }
    } else {
        if (socket.bind(broadcasting_port) != sf::Socket::Done) {
            std::cout << "Couldnot bind the socket. " << std::endl;
            exit(1);
        }
        sf::Packet packet;
        sf::IpAddress addr = sf::IpAddress::Broadcast;
        if (socket.receive(packet, addr, broadcasting_port) !=
            sf::Socket::Done) {
            std::cout << "Error while broadcasting" << std::endl;
            exit(1);
        }
        std::string result;
        packet >> result;
        std::cout << result << std::endl;
    }
    return 0;
}
