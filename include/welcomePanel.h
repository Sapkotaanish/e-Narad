#pragma once
#include "Client.hpp"
#include "Server.hpp"
#include "window.h"
#include "wx/progdlg.h"
#include <mutex>
#include <thread>
#include <wx/wx.h>

enum {
    create_button,
    join_button,
};

class WelcomePanel : public wxPanel {
private:
    wxArrayString files;
    std::thread t;
    void Initialize();
    void Send(int& stats);
    void Receive();
    bool initialized;
    bool sending, receiving;
    unsigned int sender_port, receiver_port;
    Server server;
    Client client;
    int tc{ 0 };

public:
    WelcomePanel(Window* window);
    WelcomePanel();
    Window* currentWindow;
    bool ready;
    std::mutex m;
    void onCreateClick(wxCommandEvent& event);
    void onJoinClick(wxCommandEvent& event);

    ~WelcomePanel();
};
