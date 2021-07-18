#pragma once
#include <SFML/Network.hpp>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <wx/wx.h>
struct stats {
  int current_count, total_count;
  sf::Uint64 total_size, received_size;
};
class Client {
private:
  void Connect();
  void Receive();

public:
  Client(unsigned int port);
  ~Client();
  static stats statistics;

private:
  unsigned int port;
  sf::TcpSocket socket;
  sf::IpAddress ip;
};
