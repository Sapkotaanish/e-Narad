#include "welcomePanel.h"
#include <iostream>
#include <wx/wx.h>

WelcomePanel::WelcomePanel(Window *window)
    : wxPanel(window, wxID_ANY, wxDefaultPosition, wxSize(200, 800)),
      initialized(false) {

    currentWindow = window;

    wxButton *createButton = new wxButton(this, create_button, "Send",
                                          wxDefaultPosition, wxSize(150, 40));
    wxButton *joinButton = new wxButton(this, join_button, "Receive",
                                        wxDefaultPosition, wxSize(150, 40));

    wxBoxSizer *pSizer = new wxBoxSizer(wxVERTICAL);
    sending = false;
    pSizer->AddStretchSpacer(1);
    pSizer->Add(createButton, 0, wxALIGN_CENTER);
    pSizer->Add(joinButton, 0, wxALIGN_CENTER);
    pSizer->AddStretchSpacer(1);

    this->SetSizer(pSizer);
    this->Layout();

    // opens file dialog on click
    Connect(create_button, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(WelcomePanel::onCreateClick));
    joinButton->Bind(wxEVT_BUTTON, &WelcomePanel::onJoinClick, this);
};

void WelcomePanel::onCreateClick(wxCommandEvent &event) {

    if (!initialized) {
        sender_port = 50000;
        receiver_port = 48000;
        initialized = true;
    }

    if (!sending) {
        wxFileDialog *openFileDialog = new wxFileDialog(
            this, "", "", "", "", wxFD_MULTIPLE | wxFD_PREVIEW);
        if (openFileDialog->ShowModal() == wxID_OK) {
            openFileDialog->GetPaths(files);
            std::thread thr(&WelcomePanel::Send, this);
            thr.detach();
        }
    } else {
        wxMessageBox("Please wait for the transfer of previous file.", "",
                     wxICON_ERROR);
    }
};

void WelcomePanel::onJoinClick(wxCommandEvent &event) {
    currentWindow->setStatus("Receiving...");
    if (!initialized) {
        sender_port = 48000;
        receiver_port = 50000;
        initialized = true;
    }
    if (!receiving) {
        std::thread thr(&WelcomePanel::Receive, this);
        thr.detach();
    } else {
        wxMessageBox("Please wait, you are already receiving files.", "",
                     wxICON_ERROR);
    }
};

void WelcomePanel::Send() {
    std::mutex m;
    m.lock();
    sending = true;
    if (!server.initialized)
        server.Initialize(sender_port);
    server.Send(files);
    sending = false;
    m.unlock();
}

void WelcomePanel::Receive() {
    std::mutex m;
    m.lock();
    receiving = true;
    if (!client.initialized)
        client.Initialize(receiver_port);
    client.Receive();
    receiving = false;
    m.unlock();
}

WelcomePanel::~WelcomePanel() {
    std::cout << "its working dick heads." << std::endl;
}
