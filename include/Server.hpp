#pragma once
#include <wx/wx.h>
#include <SFML/Network.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

class Server
{
private:
  void Listen();
  void Accept();
  void Send();

public:
  Server(unsigned int port, wxArrayString files);
  ~Server();

private:
  unsigned int port;
  wxArrayString files;
  sf::TcpListener listener;
  sf::TcpSocket client;
};
