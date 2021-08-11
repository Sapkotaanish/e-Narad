#pragma once
#include "window.h"
#include "wx/progdlg.h"
#include <mutex>
#include <thread>
#include "Board.h"
#include <wx/wx.h>
#include "Client.hpp"
#include "Server.hpp"
// #include "Board.h"

enum {
    send_button,
    receive_button,
    disconnect_button,
    play_tictactoe
};

class WelcomePanel : public wxPanel {
private:
    wxArrayString files;
    std::thread t;
    void Initialize();
    void Send(int& stats);
    void Receive();
    void PlayGame();
    bool initialized;
    bool sending, receiving, playing_game;
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
    void onSendClick(wxCommandEvent& event);
    void onReceiveClick(wxCommandEvent& event);
    void onDisconnectClick(wxCommandEvent& event);
    void onPlayTicTacToeClick(wxCommandEvent& event);
    ~WelcomePanel();
};
