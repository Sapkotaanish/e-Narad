#include "../include/Client.hpp"

Client::Client(unsigned int port):port(port) {
    ip = sf::IpAddress::getLocalAddress();
    Connect();
}

void Client::Connect() {
    if(socket.connect(ip, port) == sf::Socket::Done){
        std::cout << "Reached to connection";
        return;
    }
    else {
         Client::Connect();
    }
}


void Client::receive(std::string dest_file) {
    struct stat buf;
    std::fstream outfile(dest_file,std::ios::out |  std::ios::binary);
if(!outfile.is_open()){
        std::cout << "File cannot be opened" << std::endl;
        exit(1);
    }
    sf::Uint32 size;
    sf::Packet packet;
    std::size_t byte_received;
    socket.receive(packet);
    packet >> size;
    int size_of_file   =  (int)size;
    unsigned int packet_size = size_of_file<300?size_of_file:300;
    char data[packet_size];
    int received_size = 0;
    float percentage = 0;
    while(received_size < size_of_file) {
        socket.receive(data, packet_size, byte_received);
        outfile.write(data, packet_size);
        received_size += byte_received;
        percentage = received_size / size_of_file * 100;
        if(percentage - int(percentage) == 0)
            std::cout << int(percentage) << "% completed." << std::endl;
    }
    outfile.close();
    packet << "Completed.";
    socket.send(packet);

}

Client::~Client(){
    socket.disconnect();

}
