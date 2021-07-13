#pragma once
#include <wx/wx.h>
#include <SFML/Network.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

class Server
{
private:
  void Listen();
  void Accept();
  void Send();

public:
<<<<<<< HEAD
  Server(unsigned int port);
  void start();
  void send(std::string file_name);
=======
  Server(unsigned int port, wxArrayString files);
>>>>>>> 9b5ac9b0ba51a33dcacfbbe2495082f2f8007314
  ~Server();

private:
  unsigned int port;
  wxArrayString files;
  sf::TcpListener listener;
  sf::TcpSocket client;
};
