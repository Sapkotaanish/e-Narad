#include "../include/Server.hpp"
#include <thread>
Server::Server(unsigned int port, wxArrayString files)
    : port(port), files(files) {
    Listen();
    Accept();
    Send();

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
    if (listener.accept(client) != sf::Socket::Done) {
        listener.close();
        std::cout << "Error while accepting." << std::endl;
        exit(1);
    }
    else {
        std::cout << "Connected to receiver with IP " << client.getRemoteAddress()
            << " .";
        std::cout << "My IP " << sf::IpAddress::getLocalAddress() << std::endl;
    }
}

void Server::Send() {
    sf::Packet packet;
    sf::Uint8 file_count = files.GetCount();
    std::cout << "File count in server: " << (int)file_count << std::endl;
    packet << file_count;
    Server::statistics.total_count = file_count;
    client.send(packet);
    int count = 0;

    for (auto i : files) {
        std::ifstream i_file(i, std::ios::ate | std::ios::binary);
        if (!i_file.is_open()) {
            std::cout << "Error opening file" << std::endl;
            listener.close();
            exit(1);
        }
        Server::statistics.current_count = ++count;
        sf::Packet packet;
        std::size_t size = i_file.seekg(0, std::ios::end).tellg();
        std::cout << "Size: " << size << std::endl;
        std::size_t sendable_size = size;
        Server::statistics.total_size = (sf::Uint64)sendable_size;
        packet << static_cast<std::string>(i);
        packet << (sf::Uint64)sendable_size;
        client.send(packet);
        const size_t packet_size =
            sendable_size < 10000 ? sendable_size : 10000;
        std::cout << "Packet size in server: " << packet_size << std::endl;
        char data[packet_size];
        i_file.seekg(0, std::ios::beg);
        size_t sent_size = 0;


        while (!i_file.eof()) {
            i_file.read(data, packet_size);
            client.send(data, packet_size);
            sent_size += packet_size;
            Server::statistics.sent_size = sent_size;
            percentage = (((float)Server::statistics.sent_size * 100.f) / (float)Server::statistics.total_size);
            wxLogStatus(wxT("Sending... : %d / %d ( %d% )"), Server::statistics.current_count, Server::statistics.total_count, percentage);
        }
        if (percentage == 100 && (Server::statistics.current_count == Server::statistics.total_count)) {
            wxLogMessage(wxT("Completed"));
            wxLogStatus(wxT("Sent successfully"));
        }
        Server::statistics.sent_size = 0;
        i_file.close();
        client.receive(packet);
        std::string s;
        packet >> s;
    }
}



Server::~Server() {
    client.disconnect();
    listener.close();
}

Server::stats Server::statistics{ 0, 0, 0, 0 };
