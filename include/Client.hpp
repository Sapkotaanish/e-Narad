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
  float percentage_received{ 0 };
  static unsigned int count;
  Client() {};
  Client(unsigned int port);
  ~Client();

private:
  unsigned int port;
  sf::TcpSocket socket;
  sf::IpAddress ip;
};
