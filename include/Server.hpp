#pragma once

#include <SFML/Network.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

class Server {
private:
  void Listen();
  void Accept();

public:
  Server(unsigned int port);
  void start();
  void send(std::string file_name);
  ~Server();

private:
  unsigned int port;
  sf::TcpListener listener;
  sf::TcpSocket client;
};
