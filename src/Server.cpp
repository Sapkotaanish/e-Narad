#include "../include/Server.hpp"
#include <thread>
Server::Server() : client_connected(false), initialized(false) {}

void Server::Initialize(unsigned int l_port) {
    port = l_port;
    std::thread t(&Server::BroadCast, this);
    Listen();
    Accept();
    if (t.joinable()) {
        t.join();
    }
    initialized = true;
}

void Server::BroadCast() {
    sf::UdpSocket socket;
    unsigned short broadcasting_port = 52000;
    sf::IpAddress address = sf::IpAddress::Broadcast;
    sf::Packet packet;
    packet << sf::IpAddress::getLocalAddress().toString();
    int count = 0;
    while (!client_connected) {
        socket.send(packet, address, broadcasting_port);
    }
}

void Server::Listen() {
    if (listener.listen(port) != sf::Socket::Done) {
        std::cout << "Error While Listening. " << std::endl;
        listener.close();
        exit(1);
    }
    else {
        std::cout << "Listened" << std::endl;
    }
}

void Server::Accept() {
    std::cout << "In accept function. " << std::endl;
    if (listener.accept(client) != sf::Socket::Done) {
        listener.close();
        std::cout << "Error while accepting." << std::endl;
        exit(1);
    }
    else {
        client_connected = true;
        std::cout << "Connected to receiver with IP "
            << client.getRemoteAddress() << " .";
        std::cout << "My IP " << sf::IpAddress::getLocalAddress() << std::endl;
    }
}

void Server::Send(wxArrayString files) {
    sf::Packet packet;
    sf::Uint8 file_count = files.GetCount();
    std::cout << "File count in server: " << (int)file_count << std::endl;
    packet << file_count;
    Server::statistics.total_count = file_count;
    client.send(packet);
    int count = 0;
    // client.receive(packet);
    for (auto i : files) {
        std::ifstream i_file(i, std::ios::ate | std::ios::binary);
        if (!i_file.is_open()) {
            std::cout << "Error opening file while reading" << std::endl;
            listener.close();
            exit(1);
        }
        Server::statistics.current_count = ++count;
        sf::Packet packet;
        std::size_t size = i_file.seekg(0, std::ios::end).tellg();
        Server::statistics.total_size = (sf::Uint64)size;
        packet << static_cast<std::string>(i);
        packet << (sf::Uint64)size;
        client.send(packet);
        const size_t packet_size = size < 10000 ? size : 10000;
        char data[packet_size];
        i_file.seekg(0, std::ios::beg);
        size_t sent_size = 0;
        std::cout << "Sending " << size << " " << i << std::endl;
        while (!i_file.eof()) {
            i_file.read(data, packet_size);
            client.send(data, packet_size);
            sent_size += packet_size;
            Server::statistics.sent_size = sent_size;
        }
        statistics.sent_size = 0;
        i_file.close();
        std::cout << "Sent: " << i << std::endl;
    }
    client.receive(packet);
}

Server::~Server() {
    client.disconnect();
    listener.close();
}
