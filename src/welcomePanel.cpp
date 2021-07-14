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

void WelcomePanel::onCreateClick(wxCommandEvent &event) {

  if (!initialized) {
    sender_port = 51000;
    receiver_port = 51001;
    initialized = true;
  }
  wxFileDialog *openFileDialog =
      new wxFileDialog(this, "", "", "", "", wxFD_MULTIPLE | wxFD_PREVIEW);
  if (openFileDialog->ShowModal() == wxID_OK) {
    openFileDialog->GetPaths(files);
    // t = std::thread(&WelcomePanel::Send, this);
    // t.join();
    std::thread thr(&WelcomePanel::Send, this);
    thr.detach();
  }
};

void WelcomePanel::onJoinClick(wxCommandEvent &event) {
  currentWindow->setStatus(wxString("Receive"));
  if (!initialized) {
    sender_port = 51001;
    receiver_port = 51000;
    initialized = true;
  }
  std::thread thr(&WelcomePanel::Receive, this);
  thr.detach();
};

void WelcomePanel::Send() { Server server(sender_port, files); }

void WelcomePanel::Receive() { Client client(receiver_port); }

WelcomePanel::~WelcomePanel() {
  std::cout << "its working dick heads." << std::endl;
  // t.join();
}
