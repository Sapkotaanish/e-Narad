#include "welcomePanel.h"


WelcomePanel::WelcomePanel(Window* window)
    : wxPanel(window, wxID_ANY), initialized(false) {

    currentWindow = window;

    wxButton* sendButton = new wxButton(this, send_button, "Send",
        wxDefaultPosition, wxSize(150, 40));
    wxButton* receiveButton = new wxButton(this, receive_button, "Receive",
        wxDefaultPosition, wxSize(150, 40));
    disconnectButton =
        new wxButton(this, disconnect_button, "Disconnect", wxDefaultPosition,
            wxSize(150, 40));
    wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);
    sending = false;
    pSizer->AddStretchSpacer(1);
    pSizer->Add(sendButton, 0, wxALIGN_CENTER);
    pSizer->AddSpacer((10, 10));
    pSizer->Add(receiveButton, 0, wxALIGN_CENTER, wxEXPAND);
    pSizer->AddSpacer((10, 10));
    pSizer->Add(disconnectButton, 0, wxALIGN_CENTER, wxEXPAND);
    pSizer->AddStretchSpacer(1);
    disconnectButton->Hide();
    this->SetSizer(pSizer);
    this->Layout();
    Connect(send_button, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(WelcomePanel::onSendClick));
    Connect(receive_button, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(WelcomePanel::onReceiveClick));
    Connect(disconnect_button, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(WelcomePanel::onDisconnectClick));
};

void WelcomePanel::onSendClick(wxCommandEvent& event) {

    if (!initialized) {
        sender_port = 50000;
        receiver_port = 48000;
        initialized = true;
    }

    if (!sending) {
        disconnectButton->Show();
        Layout();
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
            int stats{ 0 };
            wxString message;
            std::thread thr1(&WelcomePanel::Send, this, std::ref(stats));
            thr1.detach();
            bool cont{ true };
            while (stats != tc && cont) {
                message = "Sending: ";
                message << stats << "/" << tc << " \nFile: " << files[stats];

                cont = dialog.Update(stats, message);

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
            if (stats == tc) {
                wxMessageBox("Completed", "e-Narad", wxSTAY_ON_TOP);
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
        disconnectButton->Show();
        Layout();
        int tc{ 5 };
        int stats{ 0 };
        wxString currentFile = "NULL";
        std::thread thr(&WelcomePanel::Receive, this, std::ref(tc), std::ref(stats), std::ref(currentFile));
        thr.detach();
        wxProgressDialog dialog(wxT("e-Narad"), wxT("asdf"), 1,
            currentWindow,
            wxPD_CAN_ABORT |
            wxPD_ELAPSED_TIME);
        dialog.Update(0);
        dialog.Resume();
        wxString message;
        bool cont{ true };
        while (stats != tc && cont) {
            dialog.SetRange(tc);
            message = "Receiving: ";
            message << stats << "/" << tc << " \nFile: " << currentFile;

            cont = dialog.Update(stats, message);

            if (!cont) {
                if (wxMessageBox(wxT("Do you really want to cancel ? "),
                    wxT("e-Narad"),
                    wxYES_NO | wxICON_QUESTION) == wxYES) {
                    client.keepReceiving = false;
                    server.keepSending = false;
                    receiving = false;
                    sending = false;
                    wxLogStatus("Disconnected");
                    break;
                }
                dialog.Resume();
            }
            if (stats == tc) {
                wxMessageBox("Completed", "e-Narad", wxSTAY_ON_TOP);
            }
        }
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

void WelcomePanel::Receive(int& tc, int& stats, wxString& currentFile) {
    mt.lock();
    receiving = true;
    if (!client.initialized)
        client.Initialize(receiver_port);
    client.Receive(tc, stats, currentFile);
    receiving = false;
    mt.unlock();
}

void WelcomePanel::onDisconnectClick(wxCommandEvent& event) {
    disconnectButton->Hide();
    Layout();
    if (initialized) {
        wxLogStatus("Disconnected.");
        initialized = false;
        client.initialized = false;
        server.initialized = false;
        client.disconnect();
        server.disconnect();
        receiving = false;
        sending = false;
    }
    else {
        wxLogStatus("No one is connected.So no need to disconnect.");
    }
}
WelcomePanel::~WelcomePanel() { std::cout << "its working." << std::endl; }
