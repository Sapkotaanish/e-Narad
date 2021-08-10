#include "welcomePanel.h"
#include <iostream>
#include <wx/wx.h>

WelcomePanel::WelcomePanel(Window* window)
    : wxPanel(window, wxID_ANY, wxDefaultPosition, wxSize(200, 800)),
    initialized(false) {

    currentWindow = window;

    wxButton* createButton = new wxButton(this, create_button, "Send",
        wxDefaultPosition, wxSize(150, 40));
    wxButton* joinButton = new wxButton(this, join_button, "Receive",
        wxDefaultPosition, wxSize(150, 40));

    wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);
    sending = false;
    pSizer->AddStretchSpacer(1);
    pSizer->Add(createButton, 0, wxALIGN_CENTER);
    pSizer->AddSpacer((10, 10));
    pSizer->Add(joinButton, 0, wxALIGN_CENTER);
    pSizer->AddStretchSpacer(1);

    this->SetSizer(pSizer);
    this->Layout();

    // opens file dialog on click
    Connect(create_button, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(WelcomePanel::onCreateClick));
    joinButton->Bind(wxEVT_BUTTON, &WelcomePanel::onJoinClick, this);
};

void WelcomePanel::onCreateClick(wxCommandEvent& event) {

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
            wxProgressDialog dialog(wxT("e-Narad"), wxT("asdf"), 5, currentWindow, wxPD_AUTO_HIDE | wxPD_CAN_ABORT | wxPD_APP_MODAL | wxPD_ELAPSED_TIME);
            dialog.Update(0);
            dialog.Resume();
            int stats = 0;
            std::thread thr1(&WelcomePanel::Send, this, std::ref(stats));
            thr1.detach();
            bool cont = true;
            std::cout << "Total file count in wP: " << tc << std::endl;
            while (stats != tc) {
                cont = dialog.Update(stats, wxString("Sending " + stats / tc));
                if (!cont)
                {
                    if (wxMessageBox(wxT("Do you really want to cancel ? "),
                        wxT("e-Narad"),
                        wxYES_NO | wxICON_QUESTION) == wxYES) {
                        server.client.disconnect();
                        server.listener.close();
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


void WelcomePanel::onJoinClick(wxCommandEvent& event) {
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

WelcomePanel::~WelcomePanel() {
    std::cout << "its working." << std::endl;
}
