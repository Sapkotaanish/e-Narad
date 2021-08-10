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
            std::thread thr(&WelcomePanel::Initialize, this);
            thr.detach();
            wxProgressDialog dialog(wxT("example"), wxT("asdf"), 5, currentWindow, wxPD_CAN_ABORT);
            dialog.Update(0, wxT("sadf"));
            dialog.Resume();
            int stats = 0;
            std::thread thr1(&WelcomePanel::Send, this, std::ref(stats));
            thr1.detach();
            int i;
            bool cont = true;
            for(int i=1; i<=50; i++){
                wxSleep(1);
                cont = dialog.Update(stats);
                // if( !cont ){
                //     std::cout << "iscont";
                //     dialog.Resume();
                // }
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
        server.Initialize(sender_port, currentWindow);
    m.unlock();
}

void WelcomePanel::Send(int& stats){
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
