#pragma once
#include <SFML/Network.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <wx/wx.h>
struct server_stats {
    int current_count, total_count;
    sf::Uint64 total_size, sent_size;
    server_stats()
        : current_count(0), total_size(0), total_count(0), sent_size(0) {}
};
class Server {
private:
    void BroadCast();
    void Listen();
    void Accept();

public:
    server_stats statistics;
    bool initialized;
    void Send(wxArrayString files);
    void Initialize(unsigned int port);
    Server();
    ~Server();

private:
    unsigned int port;
    sf::TcpListener listener;
    sf::TcpSocket client;
    bool client_connected;
};
