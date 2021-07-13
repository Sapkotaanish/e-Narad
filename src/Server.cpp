#include "../include/Server.hpp"
<<<<<<< HEAD
#include <thread>

Server::Server(unsigned int port) : port(port) {

}

void Server::start(){
=======
Server::Server(unsigned int port, wxArrayString files) : port(port), files(files)
{
  std::cout << "HEllo world" << std::endl;
>>>>>>> 9b5ac9b0ba51a33dcacfbbe2495082f2f8007314
  Listen();
  Accept();
  Send();
}
<<<<<<< HEAD

void Server::Listen() {
  if (listener.listen(port) != sf::Socket::Done) {
=======
void Server::Listen()
{
  if (listener.listen(port) != sf::Socket::Done)
  {
>>>>>>> 9b5ac9b0ba51a33dcacfbbe2495082f2f8007314
    std::cout << "Error While Listening. " << std::endl;
    listener.close();
    exit(1);
  }
  else
  {
    std::cout << "Listened" << std::endl;
  }
}

void Server::Accept()
{
  if (listener.accept(client) != sf::Socket::Done)
  {
    listener.close();
    std::cout << "Error while accepting." << std::endl;
    exit(1);
  }
  else
  {
    std::cout << "Connected to receiver with IP " << client.getRemoteAddress()
              << " .";
    std::cout << "My IP " << sf::IpAddress::getLocalAddress() << std::endl;
  }
}

void Server::Send()
{
  sf::Packet packet;
  sf::Uint8 file_count = files.size();
  packet << file_count;
  client.send(packet);
  for (auto i : files)
  {
    std::ifstream i_file(i, std::ios::ate | std::ios::binary);
    if (!i_file.is_open())
    {
      std::cout << "Error opening file" << std::endl;
      listener.close();
      exit(1);
    }
    sf::Packet packet;
    std::size_t size = i_file.tellg();
    sf::Uint32 sendable_size = (int)size;
    packet << static_cast<std::string>(i);
    packet << sendable_size;
    client.send(packet);
    unsigned int packet_size = sendable_size < 300 ? sendable_size : 300;
    char data[packet_size];
    i_file.seekg(0, std::ios::beg);
    int sent_size = 0;
    while (!i_file.eof())
    {
      i_file.read(data, packet_size);
      client.send(data, packet_size);
      sent_size += packet_size;
    }

    i_file.close();
    client.receive(packet);
    std::string s;
    packet >> s;
  }
}
Server::~Server()
{
  client.disconnect();
  listener.close();
}
