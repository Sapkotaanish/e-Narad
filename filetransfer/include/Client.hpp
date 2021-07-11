#pragma once
#include <SFML/Network.hpp>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sys/stat.h>

class Client {
private:
  void Connect();

public:
  Client(unsigned int port);
  void receive(std::string dest_file);
  ~Client();

private:
  unsigned int port;
  sf::TcpSocket socket;
  sf::IpAddress ip;
};
