#include "../include/Server.hpp"
#include "wx/progdlg.h"
#include <thread>

Server::Server() : client_connected(false), initialized(false) {
    client.setBlocking(true);
}

void Server::Initialize(unsigned int l_port) {
    client_connected = false;
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
    unsigned short broadcasting_port{ 52000 };
    sf::IpAddress address = sf::IpAddress::Broadcast;
    sf::Packet packet;
    packet << sf::IpAddress::getLocalAddress().toString();
    int count{ 0 };
    while (!client_connected) {
        socket.send(packet, address, broadcasting_port);
    }
}

void Server::Listen() {
    if (listener.listen(port) != sf::Socket::Done) {
        std::cout << "Couldnot listen at port " << port << std::endl;
        port++;
        std::cout << "Receiving at port " << port << std::endl;
        Listen();
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

void Server::Send(wxArrayString files, int& stats) {
    sf::sleep(sf::seconds(1));
    sf::Packet fd_packet;
    sf::Uint8 file_count{ files.GetCount() };
    std::cout << "File count in server: " << static_cast<int>(file_count) << std::endl;
    fd_packet << file_count;
    Server::statistics.total_count = file_count;
    client.send(fd_packet);
    sf::Packet ack_p;
    client.receive(ack_p);
    int count{ 0 };
    for (auto i : files) {
        if (keepSending) {
            std::ifstream i_file(i, std::ios::ate | std::ios::binary);
            if (!i_file.is_open()) {
                std::cout << "Error opening file while reading" << std::endl;
                listener.close();
                exit(1);
            }
            count++;
            Server::statistics.current_count = count;
            sf::Packet file_data_packet;
            sf::Uint64 size = i_file.seekg(0, std::ios::end).tellg();
            Server::statistics.total_size = static_cast<sf::Uint64>(size);
            file_data_packet << static_cast<std::string>(i);
            file_data_packet << size;
            sf::sleep(sf::seconds(1.5));
            client.send(file_data_packet);
            const size_t packet_size = size < 1000 ? size : 1000;
            char data[packet_size];
            i_file.seekg(0, std::ios::beg);
            size_t sent_size{ 0 };
            std::cout << "Sending " << size << " " << i << std::endl;
            while (!i_file.eof()) {
                i_file.read(data, packet_size);
                client.send(data, packet_size);
                sent_size += packet_size;
                Server::statistics.sent_size = sent_size;
            }
            stats++;

            statistics.sent_size = 0;
            i_file.close();
            std::cout << "Sent: " << i << std::endl;
            sf::Packet ack;
            client.receive(ack);
        }
        else {
            std::cout << "Sending cancelled" << std::endl;
            break;
        }
    }
}

void Server::disconnect() {
    client.disconnect();
    listener.close();
    port++;
}

Server::~Server() { client.disconnect(); }
