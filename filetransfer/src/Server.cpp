#include "../include/Server.hpp"
#include "../include/Client.hpp"
/* Server::Server(unsigned int:port):port(port){ */
  Listen();
  Accept();
}
void Server::Listen() {
  if(listener.listen(port) != sf::Socket::Done) {
    std::cout << "Error While Listening. " << std::endl;
    listener.close();
    exit(1);
  }
  else {
    std::cout << "Listened" << std::endl;
  }
}

void Server::Accept() {
  if(listener.accept(client) != sf::Socket::Done) {
    listener.close();
    std::cout << "Error while accepting." << std::endl;
    exit(1);
  }
  else {
    std::cout << "Connected to receiver with IP " << client.getRemoteAddress() << " .";
    std::cout << "My IP " <<  sf::IpAddress::getLocalAddress() << std::endl;
  }
}

void Server::send(std::string src_file) {
  std::ifstream i_file(src_file, std::ios::ate | std::ios::binary);
  if(!i_file.is_open())
  {
    std::cout << "Error opening file" << std::endl;
    listener.close();
    exit(1);
  }
  sf::Packet packet;
  std::size_t size = i_file.tellg();
  sf::Uint32 sendable_size = (int) size;
  std::cout << sendable_size << " is the size of the file. " << std::endl;
  packet << sendable_size;
  client.send(packet);
  unsigned int packet_size = sendable_size < 300?sendable_size :300;
  char data[packet_size];
  i_file.seekg(0, std::ios::beg);
  int percentage = 0;
  int sent_size = 0;
  while(!i_file.eof()) {
    i_file.read(data, packet_size);
    client.send(data, packet_size);
    sent_size += packet_size;
    percentage = sent_size/ sendable_size * 100;
    if(percentage - int(percentage) == 0)
      std::cout << int(percentage) << "% completed." << std::endl;
  }

  i_file.close();
  client.receive(packet);
  std::string s;
  packet >> s;
}
Server::~Server(){
  client.disconnect();
  listener.close();
}
