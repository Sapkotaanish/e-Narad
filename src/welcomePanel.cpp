#include "welcomePanel.h"


WelcomePanel::WelcomePanel(Window* window)
    : wxPanel(window, wxID_ANY), initialized(false), playing_game(false) {

    currentWindow = window;

    wxButton* sendButton = new wxButton(this, send_button, "Send",
        wxDefaultPosition, wxSize(150, 40));
    wxButton* receiveButton = new wxButton(this, receive_button, "Receive",
        wxDefaultPosition, wxSize(150, 40));
    wxButton* disconnectButton =
        new wxButton(this, disconnect_button, "Disconnect", wxDefaultPosition,
            wxSize(150, 40));
    wxButton* playTicTacToeButton =
        new wxButton(this, play_tictactoe, "Play TicTacToe", wxDefaultPosition,
            wxSize(150, 40));
    wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);
    sending = false;
    pSizer->AddStretchSpacer(1);
    pSizer->Add(sendButton, 0, wxALIGN_CENTER);
    pSizer->AddSpacer((10, 10));
    pSizer->Add(receiveButton, 0, wxALIGN_CENTER, wxEXPAND);
    pSizer->AddSpacer((10, 10));
    pSizer->Add(disconnectButton, 0, wxALIGN_CENTER, wxEXPAND);
    pSizer->AddSpacer((10, 10));
    pSizer->Add(playTicTacToeButton, 0, wxALIGN_CENTER, wxEXPAND);
    pSizer->AddStretchSpacer(1);

    this->SetSizer(pSizer);
    this->Layout();
    Connect(send_button, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(WelcomePanel::onSendClick));
    Connect(receive_button, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(WelcomePanel::onReceiveClick));
    Connect(disconnect_button, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(WelcomePanel::onDisconnectClick));
    Connect(play_tictactoe, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(WelcomePanel::onPlayTicTacToeClick));
};

void WelcomePanel::onSendClick(wxCommandEvent& event) {

    if (!initialized) {
        sender_port = 50000;
        receiver_port = 48000;
        initialized = true;
    }

    if (!sending) {
        wxFileDialog* openFileDialog = new wxFileDialog(
            this, "", "", "", "", wxFD_MULTIPLE | wxFD_PREVIEW);
        if (openFileDialog->ShowModal() == wxID_OK) {
            openFileDialog->GetPaths(files);
            tc = files.GetCount();
            std::thread thr(&WelcomePanel::Initialize, this);
            thr.detach();
            wxProgressDialog dialog(wxT("e-Narad"), wxT("asdf"), tc,
                currentWindow,
                wxPD_AUTO_HIDE | wxPD_CAN_ABORT |
                wxPD_ELAPSED_TIME);
            dialog.Update(0);
            dialog.Resume();
            int stats = 0;
            std::thread thr1(&WelcomePanel::Send, this, std::ref(stats));
            thr1.detach();
            bool cont = true;
            std::cout << "Total file count in wP: " << tc << std::endl;
            while (stats != tc) {
                cont = dialog.Update(stats, wxString(&"Sending "[stats / tc]));
                if (!cont) {
                    if (wxMessageBox(wxT("Do you really want to cancel ? "),
                        wxT("e-Narad"),
                        wxYES_NO | wxICON_QUESTION) == wxYES) {
                        client.keepReceiving = false;
                        server.keepSending = false;
                        wxLogStatus("Disconnected");
                        break;
                    }
                    dialog.Resume();
                }
            }
        }
    }
    else {
        wxMessageBox("Please wait for the transfer of previous file.", "",
            wxICON_ERROR);
    }
};

void WelcomePanel::onReceiveClick(wxCommandEvent& event) {
    currentWindow->setStatus("Receiving...");
    if (!initialized) {
        sender_port = 48000;
        receiver_port = 50000;
        initialized = true;
    }
    if (!receiving) {
        std::thread thr(&WelcomePanel::Receive, this);
        thr.detach();
    }
    else {
        wxMessageBox("Please wait, you are already receiving files.", "",
            wxICON_ERROR);
    }
};

void WelcomePanel::Initialize() {
    m.lock();
    sending = true;
    if (!server.initialized)
        server.Initialize(sender_port);
    m.unlock();
}

void WelcomePanel::Send(int& stats) {
    m.lock();
    server.Send(files, stats);
    sending = false;
    m.unlock();
}

void WelcomePanel::Receive() {
    std::mutex mt;
    mt.lock();
    receiving = true;
    if (!client.initialized)
        client.Initialize(receiver_port);
    client.Receive();
    receiving = false;
    mt.unlock();
}

void WelcomePanel::onDisconnectClick(wxCommandEvent& event) {
    if (initialized) {
        wxLogStatus("Disconnected.");
        initialized = false;
        client.initialized = false;
        server.initialized = false;
        client.disconnect();
        server.disconnect();
    }
    else {
        wxLogStatus("No one is connected.So no need to disconnect.");
    }
}

void WelcomePanel::onPlayTicTacToeClick(wxCommandEvent& event) {
    wxLogStatus("Tictactoe started");
    if (!playing_game) {
        playing_game = true;
        std::thread game_thread(&WelcomePanel::PlayGame, this);
        game_thread.detach();
    }
    else {
        wxLogStatus("Already one instance is running.");
    }
}

void WelcomePanel::PlayGame() {
    Board b;
    b.run();
    wxLogStatus("Tic tac toe quitted.");
    playing_game = false;
}

WelcomePanel::~WelcomePanel() { std::cout << "its working." << std::endl; }
