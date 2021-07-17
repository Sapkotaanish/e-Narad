#include "../include/Client.hpp"

Client::Client(unsigned int port) : port(port) {
  ip = sf::IpAddress::getLocalAddress();
  Connect();
  Receive();
}

void Client::Connect() {
  if (socket.connect(ip, port) != sf::Socket::Done) {
    std::cout << "Error in connection" << std::endl;
    exit(1);
  }
}

void Client::Receive() {

  sf::Packet packet;
  socket.receive(packet);
  sf::Uint8 file_count;
  packet >> file_count;
  std::cout << "File count in client: " << (int)file_count << std::endl;

  count = file_count;

  for (int i = 0; i < file_count; i++) {
    struct stat buf;
    sf::Uint64 size;
    sf::Packet packet;
    std::size_t byte_received;
    socket.receive(packet);
    std::string file_name;
    packet >> file_name >> size;
    std::cout << "Size in client: " << size << std::endl;
    std::size_t size_of_file = (std::size_t)size;
    const sf::Uint64 packet_size = size_of_file < 300 ? size_of_file : 300;
    std::cout << "Packet size in client: " << packet_size << std::endl;
    char data[packet_size];
    std::size_t received_size = 0;
    const size_t last_slash_idx = file_name.find_last_of("/");
    if (std::string::npos != last_slash_idx) {
      file_name.erase(0, last_slash_idx + 1);
    }
    std::fstream outfile(file_name, std::ios::out | std::ios::binary);
    if (!outfile.is_open()) {
      std::cout << "File cannot be opened" << std::endl;
      exit(1);
    }

    while (received_size < size_of_file) {

      socket.receive(data, packet_size, byte_received);
      outfile.write(data, packet_size);
      received_size += byte_received;
      // percentage_received = ((float)received_size / (float)size_of_file) * 100;
      // std::cout << "Received: " << received_size << std::endl; /*<< "Percentage received: " << percentage_received << std::endl;*/
    }
    outfile.close();
    packet << "Completed.";
    socket.send(packet);
    count--;
  }
}
Client::~Client() { socket.disconnect(); }
unsigned int Client::count = 0;
float percentage_received{ 0.0f };
