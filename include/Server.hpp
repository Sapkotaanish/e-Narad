#pragma once
#include <SFML/Network.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <wx/wx.h>

class Server {
private:
  void BroadCast();
  void Listen();
  void Accept();
  void Send();

public:
  struct stats {
    int current_count, total_count;
    sf::Uint64 total_size, sent_size;
  };
  static stats statistics;
  Server(unsigned int port, wxArrayString files);
  ~Server();

private:
  unsigned int port;
  wxArrayString files;
  sf::TcpListener listener;
  sf::TcpSocket client;
};
