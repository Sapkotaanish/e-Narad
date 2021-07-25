#pragma once
#include <SFML/Network.hpp>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <wx/wx.h>

class Client {
private:
  void Connect();
  void Receive();

public:
  static unsigned int count;
  float percentage_received{ 0 };
  static unsigned int count;
  Client() {};
  Client(unsigned int port);
  ~Client();
  struct stats {
  public:
    int current_count, total_count;
    sf::Uint64 total_size, received_size;
  };
  static stats statistics;

private:
  unsigned int port;
  sf::TcpSocket socket;
  sf::IpAddress ip;
};
