#pragma once
#include <SFML/Network.hpp>
#include <wx/wx.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sys/stat.h>

class Client
{
private:
  void Connect();
  void Receive();

public:
  Client(unsigned int port);
  ~Client();

private:
  unsigned int port;
  sf::TcpSocket socket;
  sf::IpAddress ip;
};
