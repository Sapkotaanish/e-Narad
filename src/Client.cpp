#include "../include/Client.hpp"
using std::cout;
using std::endl;

Client::Client() {
    system("mkdir -p ~/Downloads/e-Narad");
    initialized = false;
    socket.setBlocking(true);
}

void Client::ReceiveBroadcast() {
    sf::UdpSocket udp_socket;
    unsigned short broadcasting_port = 52000;
    sf::IpAddress address = sf::IpAddress::Broadcast;
    if (udp_socket.bind(broadcasting_port) != sf::Socket::Done) {
        std::cout << "Couldnot bind the socket. " << std::endl;
        exit(1);
    }
    sf::Packet packet;
    cout << "started_receiving_for_broadcast" << endl;
    if (udp_socket.receive(packet, address, broadcasting_port) !=
        sf::Socket::Done) {
        std::cout << "Error while broadcasting" << std::endl;
        exit(1);
    }
    std::cout << "Broadcast received" << std::endl;
    std::string result;
    packet >> result;
    std::cout << result << std::endl;
    ip = result;
    udp_socket.unbind();
}

void Client::Connect() {
    if (socket.connect(ip, port, sf::seconds(2)) != sf::Socket::Done) {
        std::cout << "Couldnot connect at port " << port << std::endl;
        port++;
        std::cout << "Trying to connect at port " << port << std::endl;
        Connect();
    }
}

void Client::Initialize(unsigned int l_port) {
    port = l_port;
    ReceiveBroadcast();
    Connect();
    initialized = true;
}

void Client::Receive() {
    const char* home_dir = std::getenv("HOME");
    while (true) {
        sf::Packet fd_packet;
        socket.receive(fd_packet);
        sf::Uint8 file_count;
        fd_packet >> file_count;
        statistics.total_count = file_count;
        sf::Packet ack_packet;
        std::string ack = "received";
        ack_packet << ack;
        socket.send(ack_packet);
        for (int i = 0; i < file_count; i++) {
            if (keepReceiving) {
                statistics.current_count = i + 1;
                std::cout << statistics.current_count << std::endl;
                struct stat buf;
                sf::Uint64 size;
                sf::Packet fn_packet;
                std::size_t byte_received;
                socket.receive(fn_packet);
                std::string file_name;
                fn_packet >> file_name >> size;
                std::size_t size_of_file = (std::size_t)size;
                const sf::Uint64 packet_size =
                    size_of_file < 1000 ? size_of_file : 1000;
                statistics.total_size = size_of_file;
                char data[packet_size];
                std::size_t received_size = 0;
                const size_t last_slash_idx = file_name.find_last_of("/");
                if (std::string::npos != last_slash_idx) {
                    file_name.erase(0, last_slash_idx + 1);
                }
                file_name.insert(0, static_cast<std::string>(home_dir) +
                    "/Downloads/e-Narad/");
                std::cout << "Receiving: " << file_name << " with size " << size
                    << std::endl;
                std::fstream outfile(file_name, std::ios::out | std::ios::binary);
                if (!outfile.is_open()) {
                    std::cout << "File cannot be opened with name " << file_name << std::endl;
                    return;
                }

                while (received_size < size_of_file) {
                    socket.receive(data, packet_size, byte_received);
                    outfile.write(data, packet_size);
                    received_size += byte_received;
                    statistics.received_size = received_size;
                }
                statistics.received_size = 0;
                std::cout << "Received " << file_name << std::endl;
                outfile.close();
                sf::Packet acknowledgement;
                acknowledgement << "acknowledgement of Completion.";
                socket.send(acknowledgement);
            }
            else {
                std::cout << "Receiving cancelled" << std::endl;
                break;
            }
        }
    }
}

void Client::disconnect(){
  socket.disconnect();
}
Client::~Client() { socket.disconnect(); }
