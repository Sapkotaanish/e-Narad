#pragma once
#include <SFML/Network.hpp>
#include <fstream>
#include <iostream>

class Download {
private:
  sf::Http Http;
  sf::Http::Request Request;
  unsigned int Filesize;
  std::string FileContainer;
  unsigned short port;
  sf::Http::Response Page;
  std::string Host, RemoteFile, LocalFile;
  std::ofstream outfile;

public:
  Download(const std::string Host, const std::string RemoteFile,
           const std::string LocalFile, unsigned short port = 0);
  void download();
};
