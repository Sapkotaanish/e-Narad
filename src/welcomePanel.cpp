#include <wx/wx.h>
#include <iostream>
#include "welcomePanel.h"

WelcomePanel::WelcomePanel(Window *window) : wxPanel(window, wxID_ANY, wxDefaultPosition, wxSize(200, 800)){

    currentWindow = window;

    wxButton *createButton = new wxButton(this, create_button, "Create Hotspot", wxDefaultPosition, wxSize(150,40));
    wxButton *joinButton = new wxButton(this, join_button, "Join Hotspot", wxDefaultPosition, wxSize(150,40));

    wxBoxSizer * pSizer = new wxBoxSizer( wxVERTICAL );

    pSizer->AddStretchSpacer(1);
    pSizer->Add(createButton, 0, wxALIGN_CENTER);
    pSizer->AddSpacer((10, 10));
    pSizer->Add(joinButton, 0, wxALIGN_CENTER);
    pSizer->AddStretchSpacer(1);

    this->SetSizer(pSizer);
    this->Layout();

    createButton->Bind(wxEVT_BUTTON, &WelcomePanel::onCreateClick, this);
    joinButton->Bind(wxEVT_BUTTON, &WelcomePanel::onJoinClick, this);

};

void WelcomePanel::onCreateClick(wxCommandEvent &event){
    currentWindow->setStatus(wxString("Creating Hotspot"));
};

void WelcomePanel::onJoinClick(wxCommandEvent &event){
    currentWindow->setStatus(wxString("Joining Hotspot"));
};