#include "../include/Client.hpp"

Client::Client(unsigned int port) : port(port) {
  system("mkdir -p ~/Downloads/e-Narad");
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
  const char *home_dir = std::getenv("HOME");
  sf::Packet packet;
  socket.receive(packet);
  sf::Uint8 file_count;
  packet >> file_count;
  statistics.total_count = file_count;
  for (int i = 0; i < file_count; i++) {
    statistics.current_count = i + 1;
    struct stat buf;
    sf::Uint64 size;
    sf::Packet packet;
    std::size_t byte_received;
    socket.receive(packet);
    std::string file_name;
    packet >> file_name >> size;
    std::cout << "Size in client: " << size << std::endl;
    std::size_t size_of_file = (std::size_t)size;
    statistics.total_size = size_of_file;
    const sf::Uint64 packet_size = size_of_file < 10000 ? size_of_file : 10000;
    std::cout << "Packet size in client: " << packet_size << std::endl;
    char data[packet_size];
    std::size_t received_size = 0;
    const size_t last_slash_idx = file_name.find_last_of("/");
    if (std::string::npos != last_slash_idx) {
      file_name.erase(0, last_slash_idx + 1);
    }
    file_name.insert(0, static_cast<std::string>(home_dir) +
                            "/Downloads/e-Narad/");
    std::cout << file_name << std::endl;
    std::fstream outfile(file_name, std::ios::out | std::ios::binary);
    if (!outfile.is_open()) {
      std::cout << "File cannot be opened" << std::endl;
      exit(1);
    }

    while (received_size <= size_of_file) {
      socket.receive(data, packet_size, byte_received);
      outfile.write(data, packet_size);
      received_size += byte_received;
      statistics.received_size = received_size;
    }
    statistics.received_size = 0;
    outfile.close();
    packet << "Completed.";
    socket.send(packet);
  }
}
Client::~Client() { socket.disconnect(); }

Client::stats Client::statistics{0, 0, 0, 0};
