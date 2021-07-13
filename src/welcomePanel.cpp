#include <wx/wx.h>
#include <iostream>
#include "welcomePanel.h"

WelcomePanel::WelcomePanel(Window* window) : wxPanel(window, wxID_ANY, wxDefaultPosition, wxSize(200, 800))
{

    currentWindow = window;

    wxButton* createButton = new wxButton(this, create_button, "Send", wxDefaultPosition, wxSize(150, 40));
    wxButton* joinButton = new wxButton(this, join_button, "Receive", wxDefaultPosition, wxSize(150, 40));

    wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);

    pSizer->AddStretchSpacer(1);
    pSizer->Add(createButton, 0, wxALIGN_CENTER);
    pSizer->AddSpacer((10, 10));
    pSizer->Add(joinButton, 0, wxALIGN_CENTER);
    pSizer->AddStretchSpacer(1);

    this->SetSizer(pSizer);
    this->Layout();

    //opens file dialog on click
    Connect(create_button, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(WelcomePanel::onCreateClick));
    joinButton->Bind(wxEVT_BUTTON, &WelcomePanel::onJoinClick, this);
};

void WelcomePanel::onCreateClick(wxCommandEvent& event)
{

    wxFileDialog* openFileDialog = new wxFileDialog(this, "", "", "", "", wxFD_MULTIPLE | wxFD_PREVIEW);
    if (openFileDialog->ShowModal() == wxID_OK)
    {
        openFileDialog->GetPaths(files);
        t = std::thread(&WelcomePanel::Send, this);
    }
};

void WelcomePanel::onJoinClick(wxCommandEvent& event)
{
    t = std::thread(&WelcomePanel::Receive, this);
    currentWindow->setStatus(wxString("Receive"));
};

void WelcomePanel::Send()
{
    Server server(51000, files);
}

void WelcomePanel::Receive()
{
    Client client(51000);
}

WelcomePanel::~WelcomePanel()
{
    t.join();
}
