#pragma once
#include <SFML/Network.hpp>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <wx/wx.h>

struct client_stats {
    int current_count, total_count;
    sf::Uint64 total_size, received_size;
    client_stats()
        : current_count(0), total_count(0), total_size(0), received_size(0) {}
};

class Client {
private:
    void Connect();
    void ReceiveBroadcast();

public:
    Client();
    ~Client();
    client_stats statistics;
    bool initialized;
    void Initialize(unsigned int port);
    void Receive(int& tc, int& stats, wxString& currentFile);
    bool keepReceiving{ true };
    void disconnect();

private:
    unsigned int port;
    sf::TcpSocket socket;
    sf::IpAddress ip;
};
