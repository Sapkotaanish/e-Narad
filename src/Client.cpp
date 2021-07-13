#include "../include/Client.hpp"

Client::Client(unsigned int port) : port(port)
{
  ip = sf::IpAddress::getLocalAddress();
  Connect();
  Receive();
}

void Client::Connect()
{
  if (socket.connect(ip, port) == sf::Socket::Done)
  {
    std::cout << "Reached to connection";
    return;
  }
  else
  {
    Client::Connect();
  }
}

void Client::Receive()
{
  sf::Packet packet;
  socket.receive(packet);
  sf::Uint8 file_count;
  packet >> file_count;
  for (int i = 0; i < file_count; i++)
  {
    struct stat buf;
    sf::Uint32 size;
    sf::Packet packet;
    std::size_t byte_received;
    socket.receive(packet);
    std::string file_name;
    packet >> file_name >> size;
    int size_of_file = (int)size;
    unsigned int packet_size = size_of_file < 300 ? size_of_file : 300;
    char data[packet_size];
    int received_size = 0;
    const size_t last_slash_idx = file_name.find_last_of("/");
    if (std::string::npos != last_slash_idx)
    {
      file_name.erase(0, last_slash_idx + 1);
    }
    std::fstream outfile(file_name, std::ios::out | std::ios::binary);
    if (!outfile.is_open())
    {
      std::cout << "File cannot be opened" << std::endl;
      exit(1);
    }

    while (received_size < size_of_file)
    {
      socket.receive(data, packet_size, byte_received);
      outfile.write(data, packet_size);
      received_size += byte_received;
    }
    outfile.close();
    packet << "Completed.";
    socket.send(packet);
    std::cout << "Completed transfer of " << i+ 1 << " file.";
  }
}
Client::~Client() { socket.disconnect(); }
